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
	fprintf(cgiOut,"body{background-image:url(../image/s.jpg);background-repeat:no-repeat;background-position:center}\n");
	fprintf(cgiOut,"</style>\n");
	fprintf(cgiOut,"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"/>");
	fprintf(cgiOut,"</head>\n");

	if(cgiFormSuccess==cgiFormSubmitClicked("bt_register"))// 若为注册按钮
	{		
		fprintf(cgiOut,"<body>\n");
		fprintf(cgiOut,"<H1 align=\"center\">正在强力跳转注册页面中</H1>");
		fprintf(cgiOut,"<meta http-equiv=\"refresh\" content=\"1;url=../register.html\"/>");
		return 0;
	/*
		   cgiFormString("user",shm->shm_user,sizeof(shm->shm_user));
		   cgiFormString("passwd",shm->shm_passwd,sizeof(shm->shm_passwd)); 
		   shm->f_flag='R';
		//将用户名密码存在共享内存，传到主程序注册		
		if(cgiFormSuccess==cgiFormSubmitClicked("submit"))
		{

			if(shm->flag=='C')
			{
				fprintf(cgiOut,"注册成功！\n");
				fprintf(cgiOut,"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"/ >");
				fprintf(cgiOut,"<meta http-equiv=\"refresh\" content=\"1;url=../index.html\"/>");
			}	
			else if(shm->flag=='B')
			{
				fprintf(cgiOut,"注册失败，请重新注册！\n");
				fprintf(cgiOut,"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />");
				fprintf(cgiOut,"<meta http-equiv=\"refresh\" content=\"1\">\n");
			}

		}
*/
	}
	/*登录*/

	if(cgiFormSuccess==cgiFormSubmitClicked("bt_login"))
	{	

		sqlite3 *db;
		if(SQLITE_OK!=sqlite3_open("usr.db",&db))
		{
			fprintf(cgiOut,"<body>\n");
			fprintf(cgiOut, "<H1>%s</H1>", "Server is busy...");
			fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"1;url=../index.html\"/>");
			return -1;
		}
		char sql[128];
		char **result;
		int row,column;
		sprintf(sql,"select * from user where name ='%s' and passwd='%s';",username,userpasswd);
		if(sqlite3_get_table(db, sql, &result, &row, &column, NULL) != SQLITE_OK)
		{
			fprintf(cgiOut, "<body>");
			fprintf(cgiOut, "<H1>%s</H1>", "Server is busy...");
			fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"1;url=../index.html\"/>");
			sqlite3_close(db);
			return -1;
		}

		if(row == 0)
		{
			fprintf(cgiOut, "<body>");
			fprintf(cgiOut, "<H1>%s</H1>", "Name or password error");
			fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"1;url=../index.html\"/>");
			sqlite3_close(db);
			return 0;
		}
		strcpy(login_name,username);
		fprintf(cgiOut, "<body>");
		fprintf(cgiOut, "<H1 align=\"center\">%s</H1>", "Login Success");
		fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"1;url=../main.html\"/>");

		sqlite3_close(db);
	}
		/*登录*/
#if 0
		if(cgiFormSuccess==cgiFormSubmitClicked("bt_login"))
		{	

			memset(shm->shm_user,0,sizeof(shm->shm_user));	
			memset(shm->shm_passwd,0,sizeof(shm->shm_passwd));
			cgiFormString("user",shm->shm_user,sizeof(shm->shm_user));
			cgiFormString("passwd",shm->shm_passwd,sizeof(shm->shm_passwd));
		shm->f_flag='L';


		fprintf(cgiOut,"%c\n",shm->flag);
		if(shm->flag=='S')
		{	
			fprintf(cgiOut,"%c\n",shm->flag);
			shm->flag='A';
			fprintf(cgiOut,"登录成功！\n");				
			fprintf(cgiOut,"<meta http-equiv=\"refresh\" content=\"1;url=../main.html\">\n");
		}

		else if(shm->flag=='F')
		{	
			fprintf(cgiOut,"%c\n",shm->flag);
			shm->flag='A';
			fprintf(cgiOut,"登录失败！\n");
			fprintf(cgiOut,"<meta http-equiv=\"refresh\" content=\"1;url=../index.html\">\n");
		}
	}
#endif
	fprintf(cgiOut,"</body>\n");
	fprintf(cgiOut,"</html>\n");
}
