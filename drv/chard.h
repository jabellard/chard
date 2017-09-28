#ifndef CHARD_H
#define CHARD_H

#define MEMORY_AREA_SIZE 256
#define NUM_DEVICES 1
#define DEVICE_NAME "chard0"
#define CLASS_NAME "chard"
#include <linux/cdev.h>


typedef struct _chard
{
	char memory_area[MEMORY_AREA_SIZE];
	struct cdev device;
	struct semaphore sem;
}chard; // end struct _chard


// function prototypes------------------
static int chard_open(struct inode *inodep, struct file *filep);
static ssize_t chard_read(struct file *filep, char *buffer, size_t len, loff_t *offset);
static ssize_t chard_write(struct file *filep, const char *buffer, size_t len, loff_t *offset);
static int chard_release(struct inode *inodep, struct file *filep);
static void chard_setup_cdev(chard *dev);

#endif // CHARD_H
