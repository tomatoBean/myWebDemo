#include"resources.h"

void *led_fun()
{
	int cmd;
	fd_led = open("/dev/led_demo",O_RDWR);     // 打开灯的设备节点
	if(fd_led<2)
	{
		perror("open led fail");
	}
	while(1)
	{
		pthread_mutex_lock(&mutex_led);
		pthread_cond_wait(&cond_led,&mutex_led);   //等待线程释放资源
		cmd = msg.cmd;
		pthread_mutex_unlock(&mutex_led);
		switch(cmd)
		{
		case LED_ON:
			ioctl(fd_led,FS4412_LED_ON);
		//	while(LED_ON == cmd);
		//	printf("LED_ON\n");
			break;

		case LED_OFF:
			ioctl(fd_led,FS4412_LED_OFF);
		//	printf("LED_OFF\n");
			break;

		default:
			break;
		}
	}
	pthread_exit(NULL);
}
