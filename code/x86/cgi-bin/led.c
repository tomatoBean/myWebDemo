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
	char ledbuf[16];
	int cmd;	
	cgiFormStringNoNewlines("led", ledbuf, sizeof(ledbuf));

	cmd = atoi(ledbuf);
	
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
		msg.cmd = LED_ON;
	}else if(cmd == 0)
	{
		msg.cmd = LED_OFF;
	}
	msg.flag=LED_TYPE;
	msg.type = MSG_TYPE;
	msgsnd(msgid, &msg, MSG_SIZE, 0);

	cgiHeaderContentType("text/html");
	fprintf(cgiOut, "<HTML>\n");
	fprintf(cgiOut, "<TITLE>LED DEVICE</TITLE></HEAD>\n");
	fprintf(cgiOut, "<BODY bgcolor=\"#fffffffff\">\n");
	if(msg.cmd == LED_ON)
		fprintf(cgiOut, "<font size=\"8\" color = \"#ff00000000\">LED FRAMEWORK:  ON operation on LED device in cgi module</font>\n");
	else if(msg.cmd == LED_OFF)
		fprintf(cgiOut, "<font size=\"8\" color = \"#ff00000000\">LED FRAMEWORK:  OFF operation on LED device in cgi module</font>\n");
	
	//fprintf(cgiOut, "LED FRAMEWORK:  operation on LED device \n");
	//fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"0;url=../main.html\"/>");
	fprintf(cgiOut, "</BODY></HTML>\n");

	return 0;
}
