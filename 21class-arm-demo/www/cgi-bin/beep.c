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
	char beepbuf[16];
	int cmd;	
	cgiFormStringNoNewlines("radio", beepbuf, sizeof(beepbuf));
//将name值为radio的value值获取到
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
	fprintf(cgiOut, "<TITLE>beep</TITLE></HEAD>\n");
	fprintf(cgiOut, "<BODY bgcolor=\"#fffffffff\">\n");
	//fprintf(cgiOut, "<b color=\"#ff0000000\" align=\"center\">OPERATION ON LED !\n</b>");
	if(msg.cmd == BEEP_ON)
                fprintf(cgiOut, "<font size=\"8\" color = \"#ff00000000\">Enable Beep Device !</font>\n");
        else if(msg.cmd == BEEP_OFF)
                fprintf(cgiOut, "<font size=\"8\" color = \"#ff00000000\">Disable Beep Device !</font>\n");


	fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"1;url=../main.html\"/>");
	fprintf(cgiOut, "</BODY></HTML>\n");

	return 0;
}
