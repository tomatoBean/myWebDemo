#include"cgic.h"
#include"cgic.c" 
#include<string.h>
#include<errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include "sqlite3.h"
#include"video_head.h"
#define N 20

int cgiMain()
{
	char username[N];
	char userpasswd[N];

	cgiFormString("user",username,N);
	cgiFormString("passwd",userpasswd,N);

	cgiHeaderContentType("text/html\n\n");	
	fprintf(cgiOut,"<html>\n");
	fprintf(cgiOut,"<head>\n");
	fprintf(cgiOut,"<title>weclome</title>\n");
	fprintf(cgiOut,"<style type=\"text/css\">\n");
	fprintf(cgiOut,"body{background-image:url(../image/scgi.gif);background-repeat:no-repeat;background-position:center}\n");
	fprintf(cgiOut,"</style>\n");
	fprintf(cgiOut,"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />");
	fprintf(cgiOut,"</head>\n");
	sqlite3 *db;
	if(SQLITE_OK!=sqlite3_open("usr.db",&db))
	{
		fprintf(cgiOut,"<body>\n");
		fprintf(cgiOut, "<H1>%s</H1>", "Server is busy...");
		fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"1;url=../register.html\"/>");
		return -1;
	}
	char sql[128];
	char **result;
	int row,column;
	sprintf(sql,"select * from user where name ='%s';",username);
	if(sqlite3_get_table(db, sql, &result, &row, &column, NULL) != SQLITE_OK)
	{
		fprintf(cgiOut, "<body>");
		fprintf(cgiOut, "<H1>%s</H1>", "Server is busy...");
		fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"1;url=../register.html\"/>");
		sqlite3_close(db);
		return -1;
	}
	if(row!=0)
	{
		fprintf(cgiOut, "<body>");
		fprintf(cgiOut, "<H1>Sorry,用户名已存在</H1>");
		fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"1;url=../register.html\"/>");
		sqlite3_close(db);
		return -1;
	}
	if(row==0)
	{
		char *errmsg;
		fprintf(cgiOut, "<body>");
		sprintf(sql,"insert into user values('%s','%s',50,10,20,90,10000);",username,userpasswd);
		if(sqlite3_exec(db,sql,NULL,NULL,&errmsg)!=SQLITE_OK)
		{	
			fprintf(cgiOut, "<body>");
			fprintf(cgiOut, "<H1>Sorry,register fail</H1>");
			fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"1;url=../register.html\"/>");
			sqlite3_free(errmsg);
			sqlite3_close(db);
			return -1;
		}
		fprintf(cgiOut,"<H1 align=\"center\">注册成功</H1>");
		fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"1;url=../index.html\"/>");
		sqlite3_close(db);
		return 0;
	}

	fprintf(cgiOut,"</body>\n");
	fprintf(cgiOut,"</html>\n");

}
