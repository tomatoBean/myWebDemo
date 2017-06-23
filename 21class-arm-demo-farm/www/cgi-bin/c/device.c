#include "cgic.h"
#include "cgic.c"
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include "head.h"

#define SIZE 32
#define NORMAL 0
#define HIGH 	1
#define LOW 	2
#define RAINY 	3

key_t key;
int shmid;
shm_s * data_set;
size_t size=1000;
char buff[SIZE];

int cgiMain()
{
	if(-1==(key = ftok("/var/www",'y')))   //创建共享内存的ID
	{
		perror("ftok");
		exit(-1);
	}
	if((shmid = shmget(key,size,0666|IPC_CREAT | IPC_EXCL))<0) //创建获打开共享内存，获得共享内存的ID
	{
		if(errno == EEXIST)
		{
			shmid = shmget(key,size,0);
		}
		else
		{
			perror("shmget");
			exit(-1);
		}
	}
	if((data_set = (shm_s *)shmat(shmid,NULL,0))<0)       //映射共享内存，需要有指针接收共享内存的地址
	{
		perror("shmat");
		exit(-1);
	}

	cgiHeaderContentType("text/html\n\n");
	fprintf(cgiOut,"<html>\n");
	fprintf(cgiOut,"<head>\n");
	fprintf(cgiOut,"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n");
	fprintf(cgiOut,"<title>设备情况</title>\n");
	fprintf(cgiOut,"</head>\n");
	fprintf(cgiOut,"<body bgcolor=\"#BBFFFF\">\n");
	fprintf(cgiOut,"<meta http-equiv=\"refresh\" content=\"1\"/>\n");  //1秒刷新1次页面


	switch (data_set->tou_flag)
	{
	case NORMAL:
		fprintf(cgiOut,"<h2>农场人员情况：</h2>\n");
		fprintf(cgiOut,"<h2>此时无人</h2>\n");
		fprintf(cgiOut,"<h2>农场天气情况：</h2>\n");
		fprintf(cgiOut,"<h2>此刻无雨</h2>\n");
		break;
	case HIGH:
		fprintf(cgiOut,"<h2>农场人员情况：</h2>\n");
		fprintf(cgiOut,"<h2>此时有人</h2>\n");
		fprintf(cgiOut,"<h2>农场天气情况：</h2>\n");
		fprintf(cgiOut,"<h2>此刻无雨</h2>\n");
		break;
	case LOW:
		fprintf(cgiOut,"<h2>农场人员情况：</h2>\n");
		fprintf(cgiOut,"<h2>此时无人</h2>\n");
		fprintf(cgiOut,"<h2>农场天气情况：</h2>\n");
		fprintf(cgiOut,"<h2>此刻有雨</h2>\n");
		break;
	case RAINY:
		fprintf(cgiOut,"<h2>农场人员情况：</h2>\n");
		fprintf(cgiOut,"<h2>此时有人</h2>\n");
		fprintf(cgiOut,"<h2>农场天气情况：</h2>\n");
		fprintf(cgiOut,"<h2>此刻有雨</h2>\n");
		break;
	default:
		break;

	}



	fprintf(cgiOut,"<h2>温度：</h2>\n");
	switch (data_set->tm_flag)
	{
	case NORMAL:
		fprintf(cgiOut,"<h2>请您放心，温度正常</h2>\n");
		break;
	case HIGH:
		fprintf(cgiOut,"<h2>请您注意，温度过高！！！</h2>\n");
		break;
	case LOW:
		fprintf(cgiOut,"<h2>请您注意，温度过低！！！</h2>\n");
		break;
	default:
		break;

	}

	fprintf(cgiOut,"<h2>湿度：</h2>\n");
	switch (data_set->hum_flag)
	{
	case NORMAL:
		fprintf(cgiOut,"<h2>请您放心，湿度正常</h2>\n");
		break;
	case HIGH:
		fprintf(cgiOut,"<h2>请您注意，湿度过高！！！</h2>\n");
		break;
	case LOW:
		fprintf(cgiOut,"<h2>请您注意，湿度过低！！！</h2>\n");
		break;
	default:
		break;

	}
#if 0
	fprintf(cgiOut,"<h2>土壤湿度：</h2>\n");
	switch (data_set->soil_flag)
	{
	case NORMAL:
		fprintf(cgiOut,"<h2>请您放心，土壤湿度正常</h2>\n");
		break;
	case HIGH:
		fprintf(cgiOut,"<h2>请您注意，土壤湿度过高！！！</h2>\n");
		break;
	case LOW:
		fprintf(cgiOut,"<h2>请您注意，土壤湿度过低！！！</h2>\n");
		break;
	default:
		break;

	}
#endif
#if 0
	fprintf(cgiOut,"<h2>水位：</h2>\n");
	switch (data_set->lev_flag)
	{
	case NORMAL:
		fprintf(cgiOut,"<h2>请您放心，水位正常</h2>\n");
		break;
	case HIGH:
		fprintf(cgiOut,"<h2>请您注意，水位过高！！！</h2>\n");
		break;
	case LOW:
		fprintf(cgiOut,"<h2>请您注意，水位过低！！！</h2>\n");
		break;
	default:
		break;

	}
#endif

	fprintf(cgiOut,"<h2>光照：</h2>\n");
	switch (data_set->sun_flag)
	{
	case NORMAL:
		fprintf(cgiOut,"<h2>请您放心，光照正常</h2>\n");
		break;
	case HIGH:
		fprintf(cgiOut,"<h2>请您注意，光照过高！！！</h2>\n");
		break;
	case LOW:
		fprintf(cgiOut,"<h2>请您注意，光照过低！！！</h2>\n");
		break;
	default:
		break;

	}



	fprintf(cgiOut,"<h2>灯光：</h2>\n");
	if(data_set->led_flag==NORMAL)
	{
		fprintf(cgiOut,"<h2>农场灯光关闭</h2>\n");
	}
	else if(data_set->led_flag==HIGH)
	{
		fprintf(cgiOut,"<h2>农场灯光开启</h2>\n");
	}


	fprintf(cgiOut,"</body>\n");
	fprintf(cgiOut,"</html>\n");

	shmdt(data_set);
	free(data_set);
	return 0;
}

