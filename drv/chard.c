#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include "chard.h"

MODULE_DESCRIPTION("chard: character device.");
MODULE_AUTHOR("Joe Nathan Abellard");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");




static struct file_operations fops =
{
	.open = chard_open,
	.read = chard_read,
	.write = chard_write,
	.release = chard_release
}; // end struct fops

static int major_number;
static char memory_area[MEMORY_AREA_SIZE];
static int data_size;

static struct class *chard_class = NULL;
static struct device *chard_device = NULL;



static int __init chard_init(void)
{
	//printk(KERN_INFO "chard:.\n");
	printk(KERN_INFO "chard:init....\n");

	// dynamically obtain a major number
	major_number = register_chrdev(0, DEVICE_NAME, &fops);
	printk(KERN_INFO "chard:init1....\n");

	// register the class
	chard_class = class_create(THIS_MODULE, CLASS_NAME);
	printk(KERN_INFO "chard:init2....\n");

	// register the device driver
	chard_device = device_create(chard_class, NULL, MKDEV(major_number, 0), NULL, DEVICE_NAME);
	printk(KERN_INFO "chard:init3....\n");

	return 0;
} // end chard_init()

static void __exit chard_exit(void)
{
	// remove the device
	device_destroy(chard_class, MKDEV(major_number, 0));
	
	// unregister device class
	class_unregister(chard_class);
	
	// remove device class
	class_destroy(chard_class);
	
	// unregister dev #
	unregister_chrdev(major_number, DEVICE_NAME);
	printk(KERN_INFO "chard:DONE....\n");
	
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
	ret = copy_to_user(buffer, memory_area, data_size); 
	
	return (data_size = 0);
	
} // end chard_read()


static ssize_t chard_write(struct file *filep, const char *buffer, size_t len, loff_t *offset)
{
 	sprintf(memory_area, "%s(%zu letters)", buffer, len); 
 	data_size = strlen(memory_area);
 	return len;
} // end chard_write()


static int chard_release(struct inode *inodep, struct file *filep)
{
	return 0;

} // end chard_release()



module_init(chard_init);
module_exit(chard_exit);
