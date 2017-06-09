#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#define LED_MAGIC 'L'

#define LED_ON  _IOW(LED_MAGIC, 0, int)
#define LED_OFF _IOW(LED_MAGIC, 1, int)

#define     LED_MAJOR	505
#define     LED_MINOR	0
#define     LED_NUM		1
#define     LED_NAME	"led_demo"
#define     CLS_NAME	"cls_led"
#define     DEV_NAME	"led_demo"

#define GPM4CON 0x110002E0
#define GPM4DAT 0x110002E4

#define FS4412_GPX2CON  0x11000C40
#define FS4412_GPX2DAT  0x11000C44


volatile unsigned int *gpm4con;
volatile unsigned int *gpm4dat;


static unsigned int *gpx2con;
static unsigned int *gpx2dat;

dev_t devno;
struct cdev led_cdev;
struct class *cls;


int led_open (struct inode * inode, struct file *file)
{
	 printk(" led_open!!!\n");
	 return 0;
}
int led_release (struct inode *inode, struct file *file)
{
	 printk(" led_release!!!\n");
	 return 0;
}
long led_ioctl (struct file *file, unsigned int cmd, unsigned long arg)
{
	 switch (cmd)
	 {
	 case LED_ON:
			 printk(" led_on!!!\n");
		 	//*gpm4dat = (*gpm4dat)&~(0x1);
			// Turn on LED 2
                        writel(readl(gpx2dat) | 1 << 7, gpx2dat);
			 break;
	 case LED_OFF:
			 printk(" led_off!!!\n");
		 	//*gpm4dat = (*gpm4dat)|(0x1); 
			// Turn off LED 2
                        writel(readl(gpx2dat) & ~(1 << 7), gpx2dat);
			 break;
	
	 default:
		return -EFAULT;
		 break;
	 }
	 return 0;
}


struct file_operations led_fops={
	.owner = THIS_MODULE,
	.open = led_open,
	.release = led_release,
	.unlocked_ioctl = led_ioctl,
};

int __init led_init(void)
{
	int ret;
	devno = MKDEV(LED_MAJOR,LED_MINOR);
	
/*
	printk(" led_init!!!\n");
	gpm4con = ioremap(GPM4CON,0x4);
	if (NULL == gpm4con)
	{
		printk(" ioremap fail!!!\n");
		return -EFAULT;
	}
	
	gpm4dat = gpm4con + 1;
*/


  	gpx2con = ioremap(FS4412_GPX2CON, 4);
        if (gpx2con == NULL) {
                printk("ioremap gpx2con\n");
                ret = -ENOMEM;
                goto err2;
        }

        gpx2dat = ioremap(FS4412_GPX2DAT, 4);
        if (gpx2dat == NULL) {
                printk("ioremap gpx2dat\n");
                ret = -ENOMEM;
                goto err3;
        }

        // set GPX2_7 output for LED2
        writel((readl(gpx2con) & ~(0xf << 28)) | (0x1 << 28), gpx2con);
        // Turn on LED2
        writel(readl(gpx2dat) & ~(0x1<<7), gpx2dat);

        printk("Led init\n");
	

	ret = register_chrdev_region(devno,LED_NUM,LED_NAME);
	if (ret < 0)
	{
		printk(" register_chrdev_region fail!!!\n");
		return -EFAULT;
	}
	cdev_init(&led_cdev,&led_fops);
	led_cdev.owner = THIS_MODULE;
	printk(" cdev_init!!!\n");
	ret=cdev_add(&led_cdev,devno,LED_NUM);
 	if (ret < 0) {
                printk("cdev_add\n");
                goto err1;
        }
	printk(" cdev_add!!!\n");
	cls = class_create(THIS_MODULE,CLS_NAME);
	if (IS_ERR(cls))
	{
		printk(" class_create fail!!!\n");
		return -EFAULT;
	}
	printk(" class_create success!!!\n");
	device_create(cls,NULL,devno,NULL,DEV_NAME);
	//(*gpm4con) = ((*gpm4con)&~(0xf))|(0x1);
	//(*gpm4dat) = (*gpm4dat)|(0x1);

	return 0;


err3:
        iounmap(gpx2con);
err2:
        cdev_del(&led_cdev);
err1:
        unregister_chrdev_region(devno, LED_NUM);
        return ret;


}

void __exit led_exit(void)
{
	//iounmap(gpm4con);
 	iounmap(gpx2dat);
        iounmap(gpx2con);
	device_destroy(cls,devno);
	class_destroy(cls);
	cdev_del(&led_cdev);
	unregister_chrdev_region(devno,LED_NUM);
	printk(" led_exit!!!\n");
}



module_init(led_init);
module_exit(led_exit);

MODULE_LICENSE("GPL");
