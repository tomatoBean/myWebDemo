#include "cgic.h"
#include "cgic.c"
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

#define VIDEO 	 1
#define CAM 	 2
#define CAtH_VIDEO 	3
#define STOP_VIDEO 	4

typedef struct {

	long type;
	int flag;
}flag_t;

int cgiMain()
{
	key_t key;
//	char buf[2];
	int msgid;

	flag_t msg;
	msg.type=0;
	msg.flag=0;

	if((key = ftok("/var/www/",'k'))<0)
	{
		perror("ftok");
		exit(1);
	}


	if(-1 ==(msgid = msgget(key,IPC_CREAT|IPC_EXCL|0666)))
	{
		if(errno == EEXIST)
		{
			msgid = msgget(key,0);
		}else
		{
			perror("msgget");
			return -1;
		}
	}

		msg.type=VIDEO;
		msg.flag=VIDEO;

		msgsnd(msgid,&msg,sizeof(msg),0);

		cgiHeaderContentType("text/html\n\n");
		fprintf(cgiOut,"<html>\n");
		fprintf(cgiOut,"<head>\n");
		fprintf(cgiOut,"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />");
		fprintf(cgiOut,"<title>实时监控</title>\n");
		fprintf(cgiOut,"</head>\n");
	
		

			fprintf(cgiOut,"<body>\n");
			fprintf(cgiOut,"<h1>监控正在开启，请主人耐心等待......</h1>\n");
			fprintf(cgiOut,"<meta http-equiv=\"refresh\" content=\"1;url=../video.html\">\n");
			fprintf(cgiOut,"</body>\n");
			fprintf(cgiOut,"</html>\n");

		
	return 0;


}
