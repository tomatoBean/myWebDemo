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
	cgiHeaderContentType("text/html");                                                                
	fprintf(cgiOut,"<meta charset=\"utf-8\"/>");
	fprintf(cgiOut,"<BODY>");
	if(shm->hc == 1)
	{
		fprintf(cgiOut,"有人");
	}
	else{
	fprintf(cgiOut,"没人");
	}
	fprintf(cgiOut,"<meta http-equiv=\"refresh\" content=\"1\"/>");
	return 0;
}


