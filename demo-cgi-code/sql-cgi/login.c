#include  <string.h>
#include  <errno.h>
#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/msg.h>
#include  <sys/shm.h>

#include  "cgic.h"
#include  "cgic.c"
#include  "sqlite3.h"



#define N 20

int cgiMain()
{
	char username[N];
	char userpasswd[N];

	cgiFormString("name",username,N);
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


  	fprintf(cgiOut,"NAME=%s\n", username);
        fprintf(cgiOut,"PASSWD=%s\n", userpasswd);


	if(cgiFormSuccess==cgiFormSubmitClicked("myregister"))// 若为注册按钮
	{		
		fprintf(cgiOut,"<body>\n");
		fprintf(cgiOut,"<H1 align=\"center\">Just to register page.....</H1>");
		fprintf(cgiOut,"<meta http-equiv=\"refresh\" content=\"1;url=../register.html\"/>");

		return 0;
	}


	/*登录*/
	if(cgiFormSuccess==cgiFormSubmitClicked("mysubmit"))
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
		fprintf(cgiOut, "<body>");
		fprintf(cgiOut, "<H1 align=\"center\">%s</H1>", "Login Success");

		sqlite3_close(db);
	}

	fprintf(cgiOut,"</body>\n");
	fprintf(cgiOut,"</html>\n");

}
