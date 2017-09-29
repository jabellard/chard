#ifndef CHARD_H
#define CHARD_H

#include <linux/cdev.h>


typedef struct _chardev
{
	char *memory_region;
	unsigned long memory_region_size;
	struct semaphore sem;
	struct cdev *dev;
}chardev; // end struct _chard


// function prototypes------------------
static int chard_open(struct inode *inodep, struct file *filep);
static ssize_t chard_read(struct file *filep, char *buffer, size_t len, loff_t *offset);
static ssize_t chard_write(struct file *filep, const char *buffer, size_t len, loff_t *offset);
static int chard_release(struct inode *inodep, struct file *filep);
static chardev * create_chardev(void);
static void destroy_chardev(chardev *dev);

#endif // CHARD_H


