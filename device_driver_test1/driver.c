#ifndef __KERNEL__
#define __KERNEL__
#endif

#ifndef MODULE
#define MODULE
#endif

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/poll.h>

#define davidex_dev_name "kim devidex"
#define data_max_len 128

int davidex_major = 0;
static char data[data_max_len];
static int data_len;


static int davidex_open(struct inode *inode, struct file *filp)
{
	printk("davidex_open\n");
	data_len = 0;
	return 0;
}

static ssize_t davidex_read(struct file *filp, char __user *buf, size_t count, loff_t *ppos)
{
	int copylen = count;

	if(!buf) return -1;
	if(count<=0) return -1;

	if(copylen > data_len)
		copylen = data_len;

	if(copylen >0)
	{
		if(copy_to_user(buf, data, copylen * sizeof(char)))
		{
			return -1;
		}
	}

	return copylen;
}

static ssize_t davidex_write(struct file *flip, const char __user *buf, size_t count, loff_t *ppos)
{
	int copylen = count;
	if(!buf) return -1;
	if(copylen > data_max_len)
		copylen = data_max_len;
	if(copylen >0)
	{
		if(copy_from_user(data, buf, copylen*sizeof(char)))
		{
			return -1;
		}
	}

	data_len =copylen;

	return copylen;
}

static int davidex_release(struct inode *inode, struct file *filp)
{
	printk("davidex_release\n");
	return 0;
}

static struct file_operations davidex_fops=
{
	.owner=THIS_MODULE,
	.open=davidex_open,
	.release=davidex_release,
	.read=davidex_read,
	.write=davidex_write,
};

static int davidex_init(void)
{
	davidex_major=register_chrdev(0,davidex_dev_name, &davidex_fops);

	if(davidex_major>=0)
	{
		printk("register device %s Sucess (major=%d)\n", davidex_dev_name, davidex_major);
	}
	else
	{
		printk("register device %s fail\n", davidex_dev_name);
		return -EBUSY;
	}
	return 0;
}

static void davidex_exit(void)
{
	unregister_chrdev(davidex_major, davidex_dev_name);
}

module_init(davidex_init);
module_exit(davidex_exit);

MODULE_AUTHOR("exitdoor4@naver.com");
MODULE_LICENSE("Daul BSD/GPL");



