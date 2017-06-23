#include<stdio.h>
#include<stdlib.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <errno.h>

#include "cgic.h"

#include "cgic.c"

typedef struct
{
        long type;  
        int cmd;    // beep commands
        int flag;

        int tmp_max;     //温度上限
        int tmp_min;     //温度下限
}  msg_t;

msg_t msg;

#define BEEP_ON      10
#define BEEP_OFF     11

#define BEEP_TYPE    92
#define MSG_TYPE   250
#define MSG_SIZE   128

int cgiMain()
{
        int msgid, cmd;
	key_t commonkey;

	char beepbuf[16];



        system("touch test.txt");

	cgiHeaderContentType("text/html\n\n");
        fprintf(cgiOut, "<HTML>\n");
        fprintf(cgiOut, "<TITLE>BEEP TEST</TITLE></HEAD>\n");

        cgiFormStringNoNewlines("group1", beepbuf, sizeof(beepbuf));
	cmd = atoi(beepbuf);

        commonkey = ftok("/var/www/cgi-bin/",'q');
        msgid = msgget(commonkey,IPC_CREAT|IPC_EXCL|0666);

        if(msgid <0)
        {
                if(errno == EEXIST)
                {

                        msgid = msgget(commonkey, 0666);
                }
                else{
                        perror("msgget fail");
                        exit(1);
                }
        }
	
        /*  fill in message body */
        if (cmd == 1) /* value="1" */
        {
                msg.cmd = BEEP_ON; /* to open beep */
        } else if(cmd == 0) /* value="0" */
        {
                msg.cmd = BEEP_OFF; /* to close beep  */
        }

 	msg.flag=BEEP_TYPE;
        msg.type = MSG_TYPE;

        /* to send message to main process */
	msgsnd(msgid, &msg, MSG_SIZE, 0);

	/*  when user clicked ok button, beep works */
//	if(cgiFormSuccess==cgiFormSubmitClicked("OK"))
//	{
		fprintf(cgiOut,"<H1 align=\"center\">our testing message</H1>");

        	//fprintf(cgiOut, "<HTML><BODY>register is clicked....<BODY/></HTML>\n");
		if(msg.cmd == BEEP_ON)
 			fprintf(cgiOut,"<H1 align=\"center\">send on commands to beep for execution</H1>");
		else if(msg.cmd == BEEP_OFF)
 			fprintf(cgiOut,"<H1 align=\"center\">send off commands to beep for execution</H1>");
//	}


   return 0;
}
