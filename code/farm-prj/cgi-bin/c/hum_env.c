#include "cgic.h"
#include "cgic.c"
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include "head.h"

#define SIZE 64
#if 0
typedef  struct {

	float tem_tm;
	float hum_tm;
}shm_t;
#endif

key_t key;
int shmid;
shm_t *p;
float i=28.0;
size_t size=1000;
char buff[SIZE];

int cgiMain()
{
	if(-1==(key = ftok("/var/www",'k')))   //创建共享内存的ID
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
	if((p = (shm_t *)shmat(shmid,NULL,0))<0)       //映射共享内存，需要有指针接收共享内存的地址
	{
		perror("shmat");
		exit(-1);
	}

	cgiHeaderContentType("text/html\n\n");
	fprintf(cgiOut,"<html>\n");
	fprintf(cgiOut,"<head>\n");
	fprintf(cgiOut,"<title></title>\n");
	fprintf(cgiOut,"<meta http-equit\"refresh\" content\"1\">\n");  //1秒刷新1次页面
	fprintf(cgiOut,"</head>\n");
	fprintf(cgiOut,"<body bgcolor=\"#BBFFFF\">\n");

	fprintf(cgiOut,"<h2>humidity=%0.2f %%rh</h2>\n",p->hum_tm);

	fprintf(cgiOut,"</body>\n");
	fprintf(cgiOut,"</html>\n");

	shmdt(p);
	return 0;
}


