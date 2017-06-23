#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "sqlite3.h"
#include "cgic.h"
#include "cgic.c"
int t;
int h=0;
int callback(void *notuse,int argc,char ** val,char ** colname)
{
	h++;
	return 0;	
}

#define N	64

int cgiMain()
{
	char name[N] = {0};
	char pw[N] = {0};
	char sql[N] = {0};
	char sp[N] ={0};
	char **result;
	char *errmsg;
	int row, column;
	sqlite3 *db;

	cgiFormString("username", name, N);
	cgiFormString("password", pw, N);

	cgiHeaderContentType("text/html");
	fprintf(cgiOut, "<HTML>\n");
	fprintf(cgiOut, "<HTML><HEAD>\n");
	fprintf(cgiOut, "<TITLE>注册提示</TITLE></HEAD>\n");

	if(sqlite3_open("user_info.db", &db) != SQLITE_OK)
	{
		fprintf(cgiOut, "<BODY>");
		fprintf(cgiOut, "<H1>%s</H1>", "打开数据库失败");		
		fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"1;url=../index.html\">");
		return -1;
	}
//	fprintf(cgiOut,"<body>\n");
//	fprintf(cgiOut,"打开成功");

	
	if(cgiFormSuccess == cgiFormSubmitClicked("sub2"))
	{
			sprintf(sp,"select * from user_info where username='%s'", name);
		if(sqlite3_get_table(db, sp, &result, &row, &column, &errmsg) != SQLITE_OK)
		{
			fprintf(cgiOut, "<BODY>");
			fprintf(cgiOut, "<H1>%s<Hi>",errmsg);
			sqlite3_free(errmsg);
			fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"1;url=../index.html\">");
			sqlite3_close(db);
			return 0;
		}
		

			if(row ==1)
			{
				fprintf(cgiOut, "<BODY>");
				fprintf(cgiOut, "<H1>%s<Hi>","用户名已存在");
				fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"1;url=../register.html\">");
				return 0;
			}

			else
			{
				sprintf(sql, "insert into user_info values('%s','%s')", name, pw);
				t=sqlite3_exec(db,sql,NULL,NULL,&errmsg);
				fprintf(cgiOut, "<BODY>");
				fprintf(cgiOut, "<H1>%s</H1>", "注册成功");		
				fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"1;url=../index.html\">");
				sqlite3_close(db);
				return 0;
			}

	}		
		
}
