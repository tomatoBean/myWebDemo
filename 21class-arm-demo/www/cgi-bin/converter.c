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

	//msg.flag=PICTURE_TYPE;
	msg.type = MSG_TYPE;
	msgsnd(msgid, &msg, MSG_SIZE, 0);

	cgiHeaderContentType("text/html");
	fprintf(cgiOut, "<HTML>\n");
	fprintf(cgiOut, "<TITLE>picture</TITLE></HEAD>\n");

	fprintf(cgiOut, "<BODY bgcolor=\"#fffffffff\">\n");

 	if(cgiFormSuccess==cgiFormSubmitClicked("button1"))
        {
		fprintf(cgiOut, "<font size=\"8\" color = \"#ff00000000\">CONVERTING OPERATION:  </font>\n\n");
		fprintf(cgiOut, "<p align=\"center\">&nbsp;</p>");
		fprintf(cgiOut, "<font size=\"8\" color = \"#ff00000000\">##Begin with converting video clips...wait</font>\n");
		fprintf(cgiOut, "<p align=\"center\">&nbsp;</p>");
		fprintf(cgiOut, "<p align=\"center\">&nbsp;</p>");
		printf("###To begin with converting your video clips...\n");
		//system("killall mjpg_streamer");
		system("myconverter.sh &");
                //system("ffmpeg  -f video4linux2 -s 320*240 -r 10 -i /dev/video0  /motion/photo/videoR.avi &");
	}

	fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"1;url=../video.html\"/>");
	fprintf(cgiOut, "</BODY></HTML>\n");

	return 0;
}
