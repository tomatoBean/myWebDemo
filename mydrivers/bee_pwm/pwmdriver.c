#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include "pwmhead.h"

MODULE_LICENSE("Dual BSD/GPL");

#define GPD0CON_ADDRESS 0x114000A0
#define TCFG0_ADDRESS   0x139D0000

volatile unsigned int *gpd0con = NULL;
volatile unsigned int *tcfg0   = NULL;
volatile unsigned int *tcfg1   = NULL;
volatile unsigned int *tcon    = NULL;
volatile unsigned int *tcntb0  = NULL;
volatile unsigned int *tcmpb0  = NULL;

struct  class  *cls;
#define PWM_MAJOR      501
#define PWM_MINOR      0
#define PWM_DEV_NUM    1
#define PWM_DEV_NAME   "pwmdev"
#define PWM_CLS_NAME   "pwmcls"
#define PWM_DEV_MYNAME "mypwm"

int pwm_open(struct inode *node, struct file *fi)
{
	printk("pwm open");
	return 0;
}

int pwm_release(struct inode *node, struct file *fi)
{
	printk("pwm release");
	return 0;
}

ssize_t pwm_read(struct file *fi, char __user *buf, size_t size, loff_t *loff)
{
	return 0;
}

ssize_t pwm_write(struct file *fi, const char __user *buf, size_t size, loff_t *loff)
{
	return 0;
}

long pwm_unlocked_ioctl(struct file *fi, unsigned int cmd, unsigned long org)
{
	switch(cmd)
	{
		case PWM_ON:
			*tcntb0  = 1000;
			*tcmpb0  = 500;                                                                                                                             
			*tcon    = ((*tcon) & ~(0x0F << 0)) | 0x0A;
			*tcon    = ((*tcon) & ~(0x0F << 0)) | 0x09;
			break;
		case PWM_OFF:
			*tcon    = ((*tcon) & ~(0x0F << 0));
			break;
		default:
			break;
	}
	return 0;
}

dev_t devno;
struct cdev pwmdev;
struct file_operations fileops = {
	.owner   = THIS_MODULE,
	.read    = pwm_read,
	.write   = pwm_write, 
	.open    = pwm_open,
	.release = pwm_release,
	.unlocked_ioctl = pwm_unlocked_ioctl,
};

struct class *cls;
int __init pwm_driver_init(void)
{
	int ret = 0;
	printk("pwm_driver_init");
	devno = MKDEV(PWM_MAJOR,PWM_MINOR);
    ret = register_chrdev_region(devno,PWM_DEV_NUM,PWM_DEV_NAME);
	if(ret < 0)
	{
		printk("register chrdev failed!!");
		return -EFAULT;
	}
	cdev_init(&pwmdev,&fileops);
	pwmdev.owner = THIS_MODULE;
	cdev_add(&pwmdev,devno,PWM_DEV_NUM);
	cls = class_create(THIS_MODULE,PWM_CLS_NAME);
	if(cls == NULL)
	{
		printk("class_create fail!!!\n");
		return -ENOMEM;
	}
	device_create(cls,NULL,devno,NULL,PWM_DEV_MYNAME);
	gpd0con = ioremap(GPD0CON_ADDRESS,4);
	if(gpd0con == NULL)
	{
		goto err1;
	}
	tcfg0 = ioremap(TCFG0_ADDRESS,4);
	if(tcfg0 == NULL)
	{
		goto err2;
	}
	tcfg1  = tcfg0 + 1;
	tcon   = tcfg0 + 2;
	tcntb0 = tcfg0 + 3;
	tcmpb0 = tcfg0 + 4;
	*gpd0con = ((*gpd0con) & ~(0x0F << 0)) | 0x02;
	*tcfg0   = ((*tcfg0)   & ~(0xFF << 0)) | 99;
	*tcfg1   = ((*tcfg1)   & ~(0x0F << 0));
	return 0;
err2:
	printk("err2");
	iounmap(gpd0con);
err1:
	printk("err1");
	device_destroy(cls,devno);
	class_destroy(cls);
	cdev_del(&pwmdev);
	unregister_chrdev_region(devno,PWM_DEV_NUM);
	return -1;
}

void __exit pwm_driver_exit(void)
{
	printk("pwm_driver_exit");
	device_destroy(cls,devno);
	class_destroy(cls);
	cdev_del(&pwmdev);
	unregister_chrdev_region(devno,PWM_DEV_NUM);
}

module_init(pwm_driver_init);
module_exit(pwm_driver_exit);
