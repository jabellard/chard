#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <asm/uaccess.h>
#include "chard.h"
#include <linux/cdev.h>

MODULE_DESCRIPTION("chard: character device.");
MODULE_AUTHOR("Joe Nathan Abellard");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.1");




static struct file_operations fops =
{
	.owner = THIS_MODULE,
	.open = chard_open,
	.read = chard_read,
	.write = chard_write,
	.release = chard_release
}; // end struct fops

int major_number;
int first_minor_number = 0;

chard d0;
int data_size;



static int __init chard_init(void)
{
	int result;
	dev_t dev = 0;
	
	result = alloc_chrdev_region(&dev, first_minor_number, 1, "chard");
	major_number = MAJOR(dev);
	
	// init the device
	chard_setup_cdev(&d0);
	return 0;
} // end chard_init()

static void chard_setup_cdev(chard *dev)
{
	int err;
	int devno = MKDEV(major_number, first_minor_number);
	
	cdev_init(&dev->device, &fops);
	dev->device.owner = THIS_MODULE;
	dev->device.ops = &fops;
	err = cdev_add(&dev->device, devno, 1);
} // end chard_setup_cdev()


static void __exit chard_exit(void)
{

	dev_t devno = MKDEV(major_number, 0);
	cdev_del(&d0.device);
	
	unregister_chrdev_region(devno, 1);
} // end chard_exit()




static int chard_open(struct inode *inodep, struct file *filep)
{
	printk(KERN_INFO "OPENING.\n");
	return 0;
} // end chard_open()


static ssize_t chard_read(struct file *filep, char *buffer, size_t len, loff_t *offset)
{
	printk(KERN_INFO "READING.\n");
	int ret = 0;
	ret = copy_to_user(buffer, &d0.memory_area, data_size); 
	
	return (data_size = 0);
	
} // end chard_read()


static ssize_t chard_write(struct file *filep, const char *buffer, size_t len, loff_t *offset)
{
 	sprintf(&d0.memory_area, "%s(%zu letters)", buffer, len); 
 	data_size = strlen(&d0.memory_area);
 	return len;
} // end chard_write()


static int chard_release(struct inode *inodep, struct file *filep)
{
	return 0;

} // end chard_release()



module_init(chard_init);
module_exit(chard_exit);
