#include"resources.h"


void *beep_fun()
{
	int cmd;

	printf("###ENTER BEEP THREAD...");
	//fd_beep = open("/dev/mypwm",O_RDWR);     // 打开蜂鸣器 设备节点
	fd_beep = open("/dev/mypwm",O_RDWR | O_NONBLOCK);   // 打开蜂鸣器 设备节点
	if(fd_beep<2)
	{
		perror("open beep fail");
	}
	while(1)
	{
		pthread_mutex_lock(&mutex_beep);
		pthread_cond_wait(&cond_beep,&mutex_beep);  //等待线程释放资源
		cmd = msg.cmd;
		pthread_mutex_unlock(&mutex_beep);
		switch(cmd)
		{
		case BEEP_ON:
			printf("###ENTER BEEP THREAD...ON CMD");
			ioctl(fd_beep,PWM_ON);
			break;

		case BEEP_OFF:
			printf("###ENTER BEEP THREAD...OFF CMD");
			ioctl(fd_beep,PWM_OFF);
			break;
		default:
			break;
		}
	}
	pthread_exit(NULL);
}

