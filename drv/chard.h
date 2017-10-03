#ifndef CHARD_H
#define CHARD_H

#include <linux/cdev.h>
#include <linux/ioctl.h>

// charcter device object
typedef struct _chardev
{
	char *memory_region;
	int memory_region_size;
	int read_pos;
	int write_pos;
	struct semaphore sem;
	struct cdev *dev;
}chardev; // end struct _chard


// function prototypes------------------------------------------------------
static int chard_open(struct inode *inodep, struct file *filep);
static ssize_t chard_read(struct file *filep, char *buffer, size_t len, loff_t *offset);
static ssize_t chard_write(struct file *filep, const char *buffer, size_t len, loff_t *offset);
static long chard_ioctl(struct file *filep, unsigned int cmd, unsigned long arg);
static int chard_release(struct inode *inodep, struct file *filep);
static chardev * create_chardev(void);
static void destroy_chardev(chardev *dev);

// ioctl definitions------------------------------------------------------------

// the ioctl magic number
#define CHARD_IOC_MAGIC 'k'

// ioctl operations
#define CHARD_IOC_SRPOS _IOW(CHARD_IOC_MAGIC, 0, int)
#define CHARD_IOC_GRPOS _IOR(CHARD_IOC_MAGIC, 1, int)
#define CHARD_IOC_SWPOS _IOW(CHARD_IOC_MAGIC, 2, int)
#define CHARD_IOC_GWPOS _IO(CHARD_IOC_MAGIC, 3)
#define CHARD_IOC_SSIZE _IOW(CHARD_IOC_MAGIC, 4, int)
#define CHARD_IOC_RESETSIZE _IO(CHARD_IOC_MAGIC, 5)
#define CHARD_IOC_GSIZE _IO(CHARD_IOC_MAGIC, 6)

#define CHARD_IO_MAXNR 6

#endif // CHARD_H
