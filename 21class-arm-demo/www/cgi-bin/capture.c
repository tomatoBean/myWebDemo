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
 	if(cgiFormSuccess==cgiFormSubmitClicked("button1"))  // record video
        {
		msg.flag=RECORD_TYPE;
		msg.cmd=RECORD_ON;
	}

 	if(cgiFormSuccess==cgiFormSubmitClicked("button2"))  // to stop recording
        {
		msg.flag=RECORD_TYPE;
		msg.cmd=RECORD_OFF;
	}
 	if(cgiFormSuccess==cgiFormSubmitClicked("button3"))  // to reset recording
        {
		msg.flag=RECORD_TYPE;
		msg.cmd=RECORD_RESET;
	}

 	if(cgiFormSuccess==cgiFormSubmitClicked("button4")) // to snapshot
        {
		msg.flag=SNAPSHOT_TYPE;
		msg.cmd=SNAPSHOT_ON;
	}

 	if(cgiFormSuccess==cgiFormSubmitClicked("button5")) // to stop snapshot
        {

		msg.flag=SNAPSHOT_TYPE;
		msg.cmd=SNAPSHOT_OFF;
	}

 	if(cgiFormSuccess==cgiFormSubmitClicked("button6")) // to delete snapshot
	{
		msg.flag=SNAPSHOT_TYPE;
		msg.cmd=SNAPSHOT_DEL;
	}

	//msg.flag=PICTURE_TYPE;
	msg.type = MSG_TYPE;
	msgsnd(msgid, &msg, MSG_SIZE, 0);

	cgiHeaderContentType("text/html");
	fprintf(cgiOut, "<HTML>\n");
	fprintf(cgiOut, "<TITLE>picture</TITLE></HEAD>\n");
	fprintf(cgiOut, "<BODY bgcolor=\"#fffffffff\">\n");


/*
	if(cgiFormSuccess==cgiFormSubmitClicked("button3"))
        {
		printf("###To enable camera...\n");
  		system("killall mjpg_streamer");
                system("killall ffmpeg");
                system("mjpg_streamer -i \"/mjpg/input_uvc.so -y\" -o \"/mjpg/output_http.so -w /www\" &");
		fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"1;url=../monitor.html\"/>");
	}


 	if(cgiFormSuccess==cgiFormSubmitClicked("button1"))
        {
		printf("###To begin with recording...\n");
		system("killall mjpg_streamer");
                sleep(1);
                system("ffmpeg  -f video4linux2 -s 320*240 -r 10 -i /dev/video0  /motion/photo/videoR.avi &");
	}

 	if(cgiFormSuccess==cgiFormSubmitClicked("button2"))
        {
		printf("###To end with recording...\n");
    		system("killall ffmpeg");
                sleep(1);
                system("mjpg_streamer -i \"/mjpg/input_uvc.so -y\" -o \"/mjpg/output_http.so -w /www\" &");
	}

 	if(cgiFormSuccess==cgiFormSubmitClicked("button4"))
        {

		printf("###To begin with snapshot...\n");
		system("killall mjpg_streamer");
		sleep(1);
		system("killall ffmpeg");
		sleep(1);
		system("mjpg_streamer -i \"/mjpg/input_uvc.so -y\" -o \"/mjpg/output_http.so –w /www\" -o \"/mjpg/output_file.so -f /var/www/motion/photo -d 1000\" &");
	}

 	if(cgiFormSuccess==cgiFormSubmitClicked("button5"))
        {

		printf("###To end with snapshot...\n");
		system("killall mjpg_streamer");
		sleep(1);
		system("killall ffmpeg");
		sleep(1);
		system("mjpg_streamer -i \"/mjpg/input_uvc.so -y\" -o \"/mjpg/output_http.so -w /www\" &");
	}

 	if(cgiFormSuccess==cgiFormSubmitClicked("button6"))
        {

		system("rm -rf /var/www/motion/photo/1970*.jpg");
	}
*/

	fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"1;url=../monitor.html\"/>");
	fprintf(cgiOut, "</BODY></HTML>\n");

	return 0;
}
