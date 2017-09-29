#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/fcntl.h>
#include <linux/types.h>
#include <asm/uaccess.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include "chard.h"

MODULE_DESCRIPTION("chard: character device.");
MODULE_AUTHOR("Joe Nathan Abellard");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.2");



// list of file operations for the driver
static struct file_operations fops =
{
	.owner = THIS_MODULE,
	.open = chard_open,
	.read = chard_read,
	.write = chard_write,
	.release = chard_release
}; // end struct fops

// the driver's major number
static int major_number;
static int memory_region_size = 256;

// the device
static chardev *dev0;


static int __init chard_init(void)
{
	int result;
	dev_t devno;
	devno = 0;
	
	// dynamically allocate device numbers (1 major, 1+ minor)
	result = alloc_chrdev_region(&devno, 0, 1, "chard");
	if (result < 0)
	{
		return result;
	} // end if
	
	// store the major number
	major_number = MAJOR(devno);
	
	
	// create a chardev object
	dev0 = create_chardev();
	if (!dev0)
	{
		goto unreg1;
	}
	
	// initialize the chardev char dev object
	cdev_init((dev0->dev), &fops);
	
	// assign the char device to this module
	dev0->dev->owner = THIS_MODULE;
	
	// add the device to the system
	result = cdev_add((dev0->dev), devno, 1);
	if (result < 0)
	{
		goto unreg2;
	} // end if	
	
	return 0;
	unreg2:
		destroy_chardev(dev0);
	unreg1:
		unregister_chrdev_region(devno, 1);
		return result;
} // end chard_init()

static chardev * create_chardev(void)
{
	// allocate space for chardev object
	chardev *dev = kmalloc(sizeof(chardev), GFP_KERNEL);
	if (!dev)
	{
		return NULL;
	} // end if
	
	// set the size of the memory region
	dev->memory_region_size = memory_region_size;
	
	// allocate the memory region
	dev->memory_region = kmalloc(dev->memory_region_size, GFP_KERNEL);
	if (!dev->memory_region)
	{
		return NULL;
	} // end if
	
	// initialize the semaphore
	//mutex_init(&(dev->sem));
	
	// allocate a cdev structure
	dev->dev = cdev_alloc();
	if (!dev->dev)
	{
		return NULL;
	} // end if
	return dev;
} // end init_chardev()

static void destroy_chardev(chardev *dev)
{
	kfree(dev->memory_region);
	kfree(dev->dev);
	kfree(dev);
	
} // end destroy_chardev()

static void __exit chard_exit(void)
{

	dev_t devno = MKDEV(major_number, 0);
	cdev_del((dev0->dev));
	destroy_chardev(dev0);
	unregister_chrdev_region(devno, 1);
} // end chard_exit()




static int chard_open(struct inode *inodep, struct file *filep)
{
	
	// obtain the device object associated with this char device
	chardev *dev = container_of(inodep->i_cdev, chardev, dev);
	filep->private_data = dev;
	
	return 0;
} // end chard_open()


static ssize_t chard_read(struct file *filep, char *buffer, size_t len, loff_t *offset)
{
	// obatain the coresponding char device object
	chardev *dev = filep->private_data;
	
	// determine region of memory to be read
	int start = offset;
	if (start > dev->memory_region_size)
	{
		//  err
		return -1;
	} // end if
	int end = start + len;
	
	if (end > memory_region_size)
	{
		end = memory_region_size;
	} // end if
	
	copy_to_user(buffer, &(dev->memory_region[start]), end - start);
	return (end - start);
	
	
} // end chard_read()


static ssize_t chard_write(struct file *filep, const char *buffer, size_t len, loff_t *offset)
{
	// obatain the coresponding char device object
	chardev *dev = filep->private_data;
	
	// determine region of memory to be read
	int start = offset;
	if (start > dev->memory_region_size)
	{
		//  err
		return -1;
	} // end if
	int end = start + len;
	
	if (end > memory_region_size)
	{
		end = memory_region_size;
	} // end if
	
	copy_from_user(&(dev->memory_region[start]), buffer, end - start);
	return (end - start);
} // end chard_write()


static int chard_release(struct inode *inodep, struct file *filep)
{
	return 0;

} // end chard_release()



module_init(chard_init);
module_exit(chard_exit);
