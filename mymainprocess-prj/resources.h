#ifndef __VIDEO_HEAD_H_
#define __VIDEO_HEAD_H_

/*******************************头文件******************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <termios.h>
#include <sys/stat.h>
#include <fcntl.h>

/*******************************文件描述符******************************************/
int fd_beep;   //蜂鸣器
int fd_led;    //灯
int fd_dht;    //温湿度

/*******************************全局变量******************************************/
char  login_name[20];   //记录登陆人的名字；
int   mbuf[5];           //记录五个最值 的数组；




/*******************************宏定义******************************************/


#define LED_ON       2           //cgi ->  main
#define LED_OFF      3


#define LED_MAGIC 'L'

#define FS4412_LED_ON  _IOW(LED_MAGIC, 0, int)
#define FS4412_LED_OFF _IOW(LED_MAGIC, 1, int)


#define BEEP_ON      4
#define BEEP_OFF     5


#define SNAPSHOT_ON      6
#define SNAPSHOT_OFF     7
#define SNAPSHOT_DEL     8


#define RECORD_ON      9
#define RECORD_OFF     10
#define RECORD_DEL     11
#define RECORD_RESET     12




/*
#define PWM_ON    _IO('K',0)     //蜂鸣器
#define PWM_OFF   _IO('K',1)
*/

#define __PWMHEAD__
#define MAGIC     'p'
#define PWM_ON    _IO(MAGIC,0)
#define PWM_OFF   _IO(MAGIC,1)



#define TINY_LED_ON   0           //main -> tiny4412
#define TINY_LED_OFF  1           //灯


#define TMP        17     //温湿度
#define HC_SR      20     //人体感应
#define MQ_2       13     //烟雾值


#define LED_TYPE     91     //灯
#define BEEP_TYPE    92     //蜂鸣器
#define DHT_TYPE     93     // 温湿度、烟雾值上下限
#define FFMPEG_TYPE_ON  94     // 开启录像
#define FFMPEG_TYPE_OFF 95     // 关闭录像 
#define SNAPSHOT_TYPE   96     //  抓拍
#define RECORD_TYPE     100    


#define MSG_TYPE   250      //消息队列的类型
#define SHM_SIZE   1024     //共享内存空间
#define MSG_SIZE   128


/*******************************线程锁定义******************************************/
pthread_mutex_t mutex_led;
pthread_mutex_t mutex_beep;
pthread_mutex_t mutex_dht;
pthread_mutex_t mutex_snapshot;
pthread_mutex_t mutex_record;

pthread_cond_t cond_led;
pthread_cond_t cond_beep;
pthread_cond_t cond_dht;
pthread_cond_t cond_snapshot;
pthread_cond_t cond_record;
//pthread_cond_t cond_camera;
/*******************************消息队列******************************************/
typedef struct
{
	long type;
	int cmd;
	int flag;

	int tmp_max;     //温度上限
	int tmp_min;     //温度下限
	int water_max;   //湿度上限
	int water_min;   //湿度下限
	int mq_max;      //烟雾上限
}msg_t;
msg_t msg;
int msgid;

/*******************************共享内存******************************************/
typedef struct
{
	int tmp;    //温度
	int water;  //湿度
	int hc;     //人体感应
	int mq;     // 烟雾浓度
}shm_t;
shm_t *shm;
int shmid;
/*******************************************************************************/

#endif
