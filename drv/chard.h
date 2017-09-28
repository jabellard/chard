#ifndef CHARD_H
#define CHARD_H

#define MEMORY_AREA_SIZE 256
#define DEVICE_NAME "chard0"
#define CLASS_NAME "chard"

// function prototypes------------------
static int chard_open(struct inode *inodep, struct file *filep);
static ssize_t chard_read(struct file *filep, char *buffer, size_t len, loff_t *offset);
static ssize_t chard_write(struct file *filep, const char *buffer, size_t len, loff_t *offset);
static int chard_release(struct inode *inodep, struct file *filep);


#endif // CHARD_H
