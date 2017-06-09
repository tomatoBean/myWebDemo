﻿#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "sqlite3.h"
#include "cgic.h"
#include "cgic.c"

#define N	64

int cgiMain()
{
	char name[N] = {0};
	char pw[N] = {0};
	char sql[N] = {0};
	char **result;
	int row, column;
	sqlite3 *db;

	cgiFormStringNoNewlines("username", name, N);
	cgiFormStringNoNewlines("password", pw, N);

	cgiHeaderContentType("text/html");
	fprintf(cgiOut, "<HTML>\n");
	fprintf(cgiOut, "<HTML><HEAD>\n");
	fprintf(cgiOut, "<TITLE>登录提示</TITLE></HEAD>\n");

	if(sqlite3_open("user_info.db", &db) != SQLITE_OK)
	{
		fprintf(cgiOut, "<BODY>");
		fprintf(cgiOut, "<H1>%s</H1>", "打开数据库失败");		
		fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"1;url=../index.html\">");
		return -1;
	}

	if(cgiFormSuccess == cgiFormSubmitClicked("sub1"))
	{

		sprintf(sql, "select * from user_info where username='%s' and password='%s'", name, pw);

		if(sqlite3_get_table(db, sql, &result, &row, &column, NULL) != SQLITE_OK)
		{
			fprintf(cgiOut, "<BODY>");
			fprintf(cgiOut, "<H1>%s</H1>", "Server is busy...");		
			fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"1;url=../index.html\">");
			sqlite3_close(db);
			return -1;
		}

		if(row == 0)
		{
			fprintf(cgiOut, "<BODY>");
			fprintf(cgiOut, "<H1>%s</H1>", "用户名或密码错误");		
			fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"1;url=../index.html\">");
			sqlite3_close(db);
			return 0;
		}
		else
		{

			fprintf(cgiOut, "<BODY>");
			fprintf(cgiOut, "<H1>%s<H1>","Login OK!");		
			fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"1;url=../main.html\">");
			sqlite3_close(db);
			return 0;
		}
	}

	 if(cgiFormSuccess == cgiFormSubmitClicked("sub2"))
	{
		fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"1;url=../register.html\">");
	}

}
