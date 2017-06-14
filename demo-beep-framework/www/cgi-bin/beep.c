#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>

#include "cgic.c"
#include "cgic.h"

#define BEEP_ON      4
#define BEEP_OFF     5


#define MSG_TYPE   250      //消息队列的类型
#define SHM_SIZE   1024     //共享内存空间
#define MSG_SIZE   128

#define BEEP_TYPE    92     //蜂鸣器


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

msg_t msg;



int cgiMain()
{
	key_t key;
	int msgid;	
	char beepbuf[16];
	int cmd;	


	cgiFormStringNoNewlines("group1", beepbuf, sizeof(beepbuf));

	cmd = atoi(beepbuf);//将value值转换成整形
	
	if((key = ftok("/var/www/cgi-bin/", 'q')) < 0)
	{
		perror("ftok fail");
		exit(1);
	}
	msgid = msgget(key,IPC_CREAT|IPC_EXCL|0666);
	if(msgid <0)
	{
		if(errno == EEXIST)
		{

			msgid = msgget(key, 0666);
		}
		else{
			perror("msgget fail");
			exit(1);
		}
	}
	if (cmd == 1)
	{
		msg.cmd = BEEP_ON;
	}else if(cmd == 0)
	{
		msg.cmd = BEEP_OFF;
	}

	msg.flag=BEEP_TYPE;
	msg.type = MSG_TYPE;

	msgsnd(msgid, &msg, MSG_SIZE, 0);

	cgiHeaderContentType("text/html\n\n");
	fprintf(cgiOut, "<HTML>\n");
	fprintf(cgiOut, "<TITLE>BEEP</TITLE></HEAD>\n");

	if(msg.cmd == BEEP_ON)
		fprintf(cgiOut, "<H1>%s</H1>", "BEEP SHOULD BE SOUNDING NOW....");
	else if(msg.cmd == BEEP_OFF)
		fprintf(cgiOut, "<H1>%s</H1>", "BEEP SHOULD BE SILENT NOW....");

	fprintf(cgiOut, "<BODY bgcolor=\"#fffffffff\">\n");
	
	//fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"0;url=../main.html\"/>");
	fprintf(cgiOut, "</BODY></HTML>\n");

	return 0;
}
