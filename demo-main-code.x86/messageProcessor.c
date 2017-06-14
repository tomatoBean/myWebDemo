#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/ipc.h>
#include <sys/msg.h>

#include <errno.h>

#include <sys/ioctl.h>


pthread_t  mythread_led;
pthread_t  mythread_beep;
pthread_t  mythread_camera;
pthread_t  mythread_dht;

pthread_cond_t cond_beep;
pthread_mutex_t mutex_beep;


int fd_beep;   //蜂鸣器

typedef struct
{
        long type;
        int cmd;    // beep commands
        int flag;

        int tmp_max;     //温度上限
        int tmp_min;     //温度下限
        int water_max;   //湿度上限
        int water_min;   //湿度下限
        int mq_max;      //烟雾上限
}  msg_t;


#define MAGIC     'p'
#define PWM_ON    _IO(MAGIC,0)
#define PWM_OFF   _IO(MAGIC,1)

#define BEEP_ON      4
#define BEEP_OFF     5

//#define BEEP_ON      28672
//#define BEEP_OFF     28673

#define MSG_TYPE   250      //消息队列的类型
#define SHM_SIZE   1024     //共享内存空间
#define MSG_SIZE   128

#define BEEP_TYPE    92     //蜂鸣器

msg_t msg;



void *myled_fun()
{

   printf("\n###ENTER LED THREAD...\n");
}


void *mybeep_fun()
{
        int cmd;

        printf("\n###ENTER BEEP THREAD...\n");
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


/*

void *mybeep_fun()
{

   printf("###mythread_beep...\n");
}

*/


int main(int argc, const char *argv[])
{
   int i=0;
   int msgid;

    printf("home directory=%s\n", getenv("HOME"));
    printf("Parameters count: %d\n", argc);
   

    for(i=0; i<argc; i++)
    {	
    	printf("Parameter #%d = %s\n", i, argv[i]);

    }

    pthread_mutex_init(&mutex_beep,NULL);


  	/**********************创建消息队列*********************************/
 	int ret;
        key_t key_q,key_m,maxkey;

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

 

   	if(0!=pthread_create(&mythread_beep, NULL, &mybeep_fun, NULL))
   	{
       		perror("mythread_beep");
   	}

   	if(0!=pthread_create(&mythread_led, NULL, &myled_fun, NULL))
   	{
		perror("mythread_led");     
		return -1;      
   	}

 	while(1)
        {
                msgrcv(msgid,&msg,MSG_SIZE,MSG_TYPE,0);
		printf("\nmsg.flag=%d\n", msg.flag);
		printf("\nmsg.cmd=%d\n", msg.cmd);
                switch(msg.flag)
                {
			case BEEP_TYPE:
				pthread_cond_signal(&cond_beep);  // 唤醒蜂鸣器线程
				break;
			default:
				break;
                }
                sleep(2);
		//usleep(500);
        }

   if(0 != pthread_join(mythread_led,NULL))
   {
         perror("pthread_led");
                return -1;
    }

    if(0 != pthread_join(mythread_beep,NULL))
    {
          perror("pthread_beep");
          return -1;
    }
}
