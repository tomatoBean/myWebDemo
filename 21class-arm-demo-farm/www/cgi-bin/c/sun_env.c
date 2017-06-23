#include "cgic.h"
#include "cgic.c"
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include "head.h"
#define SIZE 64


//int i=100;
key_t key;
int shmid;
shm_t *data;
size_t size=1000;
char buff[SIZE];

int cgiMain()
{
	data = malloc(sizeof(shm_t));
	if(-1==(key = ftok("/var/www",'e')))   //创建共享内存的ID
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
	if((data = (shm_t *)shmat(shmid,NULL,0))<0)       //映射共享内存，需要有指针接收共享内存的地址
	{
		perror("shmat");
		exit(-1);
	}
#if 0
	cgiHeaderContentType("text/html\n\n");
	fprintf(cgiOut,"<html>\n");
	fprintf(cgiOut,"<head>\n");
	fprintf(cgiOut,"<title></title>\n");
	fprintf(cgiOut,"</head>\n");
	fprintf(cgiOut,"<body bgcolor=\"#BBFFFF\">\n");

	fprintf(cgiOut,"<h2>illumination=%d Lx </h2>\n",data->sun_tm);

	fprintf(cgiOut,"<meta http-equiv=\"refresh\" content=\"1\"/>\n");  //1秒刷新1次页面
	fprintf(cgiOut,"</body>\n");
	fprintf(cgiOut,"</html>\n");
#endif


	cgiHeaderContentType("text/html\n\n");
	fprintf(cgiOut,"<html>\n");
	fprintf(cgiOut,"<head>\n");
	fprintf(cgiOut,"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />");
	fprintf(cgiOut,"<title></title>\n");
	fprintf(cgiOut,"</head>\n");
	fprintf(cgiOut,"<body bgcolor=\"#BBFFFF\">\n");


//	fprintf(cgiOut,"<h2>%d </h2>\n",i);
	fprintf(cgiOut,"<h2>illumination= %d lx</h2>\n",data->sun_tm);
	fprintf(cgiOut,"<meta http-equiv=\"refresh\" content=\"1\"/>\n");  //1秒刷新1次页面
	fprintf(cgiOut,"</body>\n");
	fprintf(cgiOut,"</html>\n");



	shmdt(data);
	free(data);

	return 0;
}


