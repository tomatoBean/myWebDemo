#include "cgic.h"
#include "cgic.c"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include "head.h"

#define SIZE 32


key_t key;
int shmid;
shm_s *data_set=NULL;
size_t size=1000;
char buff[SIZE];

int cgiMain()
{ 	
	data_set = malloc(sizeof(shm_t));
	if(-1==(key = ftok("/home/",'y')))   //创建共享内存的ID
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
	

	cgiFormString("temmax", buff, sizeof(buff)); 		//设置农场参数
	data_set->tem_st_hight=atoi(buff);
	cgiFormString("hummax", buff, sizeof(buff));
	data_set->hum_st_high=atoi(buff);
//	cgiFormString("soilmax", buff, sizeof(buff));
//	data_set->soil_st_high=atoi(buff);
	cgiFormString("sunmax", buff, sizeof(buff));
	data_set->sun_st_high=atoi(buff);
	cgiFormString("temnin", buff, sizeof(buff));
	data_set->tem_st_low=atoi(buff);
	cgiFormString("hummin", buff, sizeof(buff));
	data_set->hum_st_low=atoi(buff);
//	cgiFormString("soilmin", buff, sizeof(buff));
//	data_set->soil_st_low=atoi(buff);
	cgiFormString("sunmin", buff, sizeof(buff));
	data_set->sun_st_low=atoi(buff);


	cgiHeaderContentType("text/html\n\n");
	fprintf(cgiOut,"<html>\n");
	fprintf(cgiOut,"<head>\n");
	fprintf(cgiOut,"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n");
	fprintf(cgiOut,"<title>set_info</title>\n");
	fprintf(cgiOut,"</head>\n");
	fprintf(cgiOut,"<body>\n");

	fprintf(cgiOut,"<h1>%s </h1>\n","设置成功.....");
	fprintf(cgiOut,"<h2>tem=%d\n</h2>\n",data_set->tem_st_hight);
	fprintf(cgiOut,"<h2>tem=%d\n</h2>\n",data_set->tem_st_low);
	fprintf(cgiOut,"<h2>hum=%d\n</h2>\n",data_set->hum_st_high);
	fprintf(cgiOut,"<h2>hum=%d\n</h2>\n",data_set->hum_st_low);
//	fprintf(cgiOut,"<h2>soil=%d\n</h2>\n",data_set->soil_st_high);
//	fprintf(cgiOut,"<h2>soil=%d\n</h2>\n",data_set->soil_st_low);
	fprintf(cgiOut,"<h2>ill=%d\n</h2>\n",data_set->sun_st_high);
	fprintf(cgiOut,"<h2>ill=%d\n</h2>\n",data_set->sun_st_low);

	fprintf(cgiOut,"<meta http-equiv=\"refresh\" content=\"1;url=../set_info.html\">\n");
	fprintf(cgiOut,"</body>\n");
	fprintf(cgiOut,"</html>\n");

	shmdt(data_set);
	return 0;
}


