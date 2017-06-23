#include "video_head.h"
#include "cgic.c"
#include "cgic.h"
int cgiMain(int argc, const char *argv[])
{
	key_t key;
 
	if(-1 == (key = ftok("/www/cgi-bin/",'m')))
	{
		perror("ftok fail");
		exit(0);
	}
	if(-1 == (shmid = shmget(key,sizeof(shm_t),IPC_CREAT|IPC_EXCL|0666)))
	{
		if(errno == EEXIST)
		{
			shmid = shmget(key,sizeof(shm_t),0);
		}else
		{ 
			perror("shmget fail");
			exit(0);
		}
	}
	shm=shmat(shmid,NULL,0);
//	printf("%s",shm.tmp);
	cgiHeaderContentType("text/html\n\n");                                                                
	fprintf(cgiOut,"<meta charset=\"utf-8\"/>");
	fprintf(cgiOut,"<BODY>");

	fprintf(cgiOut,"%d\n",shm->tmp);
//	fprintf(cgiOut,"<H1>humidity=%s<H1>\n",shmbuf1->humidity);
#if 0
	key_t mkey;
 
	if(-1 == (mkey = ftok("/var/www/cgi-bin/",'q')))
	{
		perror("ftok fail");
		exit(0);
	}
	msgid=msgget(mkey,IPC_CREAT|IPC_EXCL|0666);
	if(msgid==-1)
	{
		if(errno==EEXIST)
		{
			msgid=msgget(mkey,0666);

		}
	}
	msg.cmd=DHT_TYPE;
	msg.type=MSG_TYPE;
	msgsnd(msgid,&msg,MSG_SIZE,0);

#endif
	fprintf(cgiOut,"<meta http-equiv=\"refresh\" content=\"1\"/>");
	return 0;
}


