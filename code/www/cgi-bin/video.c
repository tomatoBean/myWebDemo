#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <errno.h>
#include "cgic.c"
#include "cgic.h"
#include "video_head.h"

int cgiMain()
{
	key_t key;
	int msgid;	

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

	msg.flag=FFMPEG_TYPE_ON;
	msg.type = MSG_TYPE;
	msgsnd(msgid, &msg, MSG_SIZE, 0);

	cgiHeaderContentType("text/html");
	fprintf(cgiOut, "<HTML>\n");
	fprintf(cgiOut, "<TITLE>picture</TITLE></HEAD>\n");
	fprintf(cgiOut, "<BODY bgcolor=\"#fffffffff\">\n");
	fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"0;url=../video.html\"/>");
	fprintf(cgiOut, "</BODY></HTML>\n");

	return 0;
}
