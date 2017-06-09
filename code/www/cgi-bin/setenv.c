#include"cgic.h"
#include"cgic.c" 
#include<string.h>
#include<errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include"video_head.h"
#define N 10
int cgiMain()
{
	char tempmaxset[N];
	char tempminset[N];	
	char humimaxset[N];
	char humiminset[N];	
	char mqmaxset[N];
#if 0
	int tempmaxi;
	int tempmini;
	int humimaxi;
	int humimini;
	int mqmaxi;
#endif
	cgiFormString("tempmax",tempmaxset,N);
	cgiFormString("tempmin",tempminset,N);
	cgiFormString("humimax",humimaxset,N);
	cgiFormString("humimin",humiminset,N);
	cgiFormString("mqmax",mqmaxset,N);
#if 0
	tempmaxi=atoi(tempmaxset);
	tempmini=atoi(tempminset);
	humimaxi=atoi(humimaxset);
	humimini=atoi(humiminset);
	mqmaxi=atoi(mqmaxset);
#endif
	cgiHeaderContentType("text/html\n\n");	
	fprintf(cgiOut,"<html>\n");
	fprintf(cgiOut,"<head>\n");
	fprintf(cgiOut,"<title>setenv</title>\n");
	fprintf(cgiOut,"<meta http-equiv=\"Content-type\" content=\"text/html; charset=utf-8\" />\n");
	fprintf(cgiOut,"</head>\n");
/*
	sqlite3 *db;
	if(SQLITE_OK!=sqlite3_open("usr.db",&db))
	{
		fprintf(cgiOut, "<body>");

		fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"1;url=../main.html\"/>");

	}
	//将网页上的温湿度、烟雾的上下限更新到数据库
	char sql[128];
	//	if(cgiFormSuccess==cgiFormSubmitClicked("set"))
	//	{
	char *errmsg;
	sprintf(sql,"update user set temp_max='%s',temp_min='%s',humi_min='%s',humi_max='%s',mq_max='%s' where name='%s';",tempmaxset,tempminset,humiminset,humimaxset,mqmaxset,login_name);
	if(sqlite3_exec(db,sql,NULL,NULL,&errmsg)!=SQLITE_OK)
	{	
		fprintf(cgiOut, "<body>");
		fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"1;url=../main.html\"/>");
		sqlite3_free(errmsg);
		sqlite3_close(db);
		return -1;
	}
	//	}

*/	
	//创建一个消息队列，用来将温湿度上下限等数据上传给主程序
	key_t key;
	key=ftok("/www/cgi-bin/",'q');
	if(key==-1)
	{
		perror("ftok fail!");
		return -1;
	}
	msgid=msgget(key,IPC_CREAT|IPC_EXCL|0666);
	if(msgid==-1)
	{
		if(errno==EEXIST)
		{
			msgid=msgget(key,0666);
		}
		else
		{
			perror("msgget fail!");
		}
	}
/*
	//从数据库中读取温湿度上下限等数据到主程序中
	char **result;
	int row,column;
	sprintf(sql,"select * from user where name ='%s';",login_name);
	if(sqlite3_get_table(db, sql, &result, &row, &column, NULL) != SQLITE_OK)
	{
		fprintf(cgiOut, "<body>\n");
		fprintf(cgiOut, "<H1>%s</H1>", "Server is busy...");
		fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"1;url=../main.html\"/>");
		sqlite3_close(db);
		return -1;
	}
	//	if(row!=0)
	//	{
*/
#if 1
	msg.type=MSG_TYPE;
	msg.flag=DHT_TYPE;
	/*
	msg.tmp_max = atoi(result[9]);
	msg.tmp_min = atoi(result[10]);
	msg.water_max = atoi(result[11]);
	msg.water_min = atoi(result[12]);
	msg.mq_max = atoi(result[13]);
	*/
	msg.tmp_max = atoi(tempmaxset);
	msg.tmp_min = atoi(tempminset);
	msg.water_max = atoi(humimaxset);
	msg.water_min = atoi(humiminset);
	msg.mq_max = atoi(mqmaxset);

	msgsnd(msgid,&msg,MSG_SIZE,0);
#endif
#if 0
	shmmix->tmp_max=*result[9];
	shmmix->tmp_min=*result[10];
	shmmix->water_min=*result[11];
	shmmix->water_max=*result[12];
	shmmix->mq_max=*result[13];
#endif

	fprintf(cgiOut, "<body>\n");
	fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"0;url=../main.html\"/>\n");
//	sqlite3_close(db);
	//	}
	fprintf(cgiOut,"</body>\n");
	fprintf(cgiOut,"</html>\n");
}
