#ifndef __KERNEL__
#define __KERNEL__
#endif

#ifndef MODULE
#define MODULE
#endif



#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/slab.h>

static char *buffer =NULL;

int test_open(struct inode *inode, struct file *filp)
{
	printk(KERN_ALERT "test_device open function called\n");
	return 0;
}

int test_device_release(struct inode *inode, struct file *filp)
{
	printk(KERN_ALERT "testdevice release function called\n");
	return 0;
}

ssize_t test_device_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
	printk(KERN_ALERT "test_device write function called\n");
	copy_from_user(buffer,buf,1024);
	return count;
}

ssize_t test_device_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
	printk(KERN_ALERT "test_device ead function called\n");
	copy_to_user(buf, buffer, 1024);
	return count;
}

static struct file_operations vd_fops = {
	.read = test_device_read,
	.write = test_device_write,
	.open = test_open,
	.release = test_device_release
};

int __init test_device_init(void)
{
	if(register_chrdev(300, "test_device", &vd_fops)<0)
		printk(KERN_ALERT "driver init failed\n");
	else
		printk(KERN_ALERT "driver init successful\n");
	buffer=(char*)kmalloc(1024, GFP_KERNEL);
	if(buffer != NULL)
		memset(buffer, 0, 1024);
	return 0;
}

void __exit test_device_exit(void)
{
	unregister_chrdev(250, "test_device");
	printk(KERN_ALERT " driver cleanup successful\n");
	kfree(buffer);
}

module_init(test_device_init);
module_exit(test_device_exit);
MODULE_LICENSE("GPL");
