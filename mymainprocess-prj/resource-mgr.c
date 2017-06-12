#include "resources.h"
#include "resource-led.c"
#include "resource-beep.c"
#include "resource-dht.c"
#include "resource-camera.c"

pthread_t pthread_led;
pthread_t pthread_beep;
pthread_t pthread_dht;
pthread_t pthread_camera;

#if 1
void init_all()
{
	pthread_mutex_init(&mutex_led,NULL);
	pthread_mutex_init(&mutex_beep,NULL);
//	pthread_mutex_init(&mutex_dht,NULL);
//	pthread_mutex_init(&mutex_camera,NULL);

	pthread_cond_init(&cond_led,NULL);
	pthread_cond_init(&cond_beep,NULL);
//	pthread_cond_init(&cond_dht,NULL);
//	pthread_cond_init(&cond_camera,NULL);
	printf("init all\n");
	return ;
}
#endif

int main(int argc, const char *argv[])
{
	init_all();
	/**********************创建共享内存*********************************/
	int ret;
	key_t key_q,key_m,maxkey;
	key_m = ftok("/var/www/cgi-bin/",'m');
	shmid = shmget(key_m,SHM_SIZE,IPC_CREAT|IPC_EXCL|0666);
	if(shmid == -1 )
	{
		if(errno = EEXIST)
		{
			printf("shm already exist!!\n");
			shmid = shmget(key_m,SHM_SIZE,0666);
		}
		else
		{
			printf("shmget fail!!\n");
		}
	}
	shm = shmat(shmid,NULL,0);
	if((void *)-1 == shm)
	{
		printf("shmat fail!!\\n");
	}

	/**********************创建消息队列*********************************/
	key_q = ftok("/var/www/cgi-bin/",'q');
	msgid = msgget(key_q,IPC_CREAT|IPC_EXCL|0666);
	if(msgid == -1 )
	{
		if(errno = EEXIST)
		{
			printf("msg already exist!!\n");
			msgid = msgget(key_q,0666);
		}
		else
		{
			printf("msgget fail!!\n");
		}
	}


	/****************************led线程************************************/
	if(0 != pthread_create(&pthread_led,NULL,led_fun,NULL))
	{
		perror("pthread_create1");
		return -1;
	}



	/****************************beep线程************************************/
	if(0 != pthread_create(&pthread_beep,NULL,beep_fun,NULL))
	{
		perror("pthread_create2");
		return -1;
	}


	/******************************DHT11温湿度线程*****************************/
	if(0 != pthread_create(&pthread_dht,NULL,dht_fun,NULL))
	{
		perror("pthread_create3");
		return -1;
	}

	/******************************照相机线程*****************************/
	if(0 != pthread_create(&pthread_camera,NULL,camera_fun,NULL))
	{
		perror("pthread_create4");
		return -1;
	}

	while(1)
	{
		msgrcv(msgid,&msg,MSG_SIZE,MSG_TYPE,0);
		switch(msg.flag)
		{
		case LED_TYPE:
			pthread_cond_signal(&cond_led);   // 唤醒led 线程 
			break;
		case BEEP_TYPE:
			pthread_cond_signal(&cond_beep);  // 唤醒蜂鸣器线程
			break;
		case DHT_TYPE:
			mbuf[0] = msg.tmp_max;      // 存储开始设置的阈值
			mbuf[1] = msg.tmp_min;
			mbuf[2] = msg.water_max;
			mbuf[3] = msg.water_min;
			mbuf[4] = msg.mq_max;
		default:
			break;
		}
		sleep(1);
	}

/******************************等待线程的结束*****************************/
	if(0 != pthread_join(pthread_led,NULL))
	{
		perror("pthread_led");
		return -1;
	}

	if(0 != pthread_join(pthread_beep,NULL))
	{
		perror("pthread_beep");
		return -1;
	}
	if(0 != pthread_join(pthread_dht,NULL))
	{
		perror("pthread_dht");
		return -1;
	}
	if(0 != pthread_join(pthread_camera,NULL))
	{
		perror("pthread_camera");
		return -1;
	}
	return 0;
}

