#include <stdio.h>
#include"cgic.h"
#include "cgic.c"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stddef.h>
#include <sys/stat.h>
#include <dirent.h>
#include <iconv.h>
#include <sys/types.h>
#include <sys/wait.h>
//#include"head.h"
int cgiMain()
{

	DIR *dir = NULL;
	struct dirent *dirp = NULL;
	dir = opendir("/var/www/motion/photo");//打开 目录读取文件名
	//chdir("/www/pice");

	if(dir == NULL)
	{
		fprintf(cgiOut, "<H2 align=\"center\">Can not open picture</H2>");	
		perror("fail to opendir");
		return -1;
	}
	cgiHeaderContentType("text/html\n\n");
	fprintf(cgiOut, "<HTML>\n");
	fprintf(cgiOut, "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">");
	fprintf(cgiOut, " <html xmlns=\"http://www.w3.org/1999/xhtml\"><head>");
	fprintf(cgiOut, "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />");//转 码
//	fprintf(cgiOut, "<link rel=\"stylesheet\" href=\"../images/style.css\" type=\"text/css\" />	<title>history Picture</title></head>");
	fprintf(cgiOut,"<title>history Picture</title></head>");
	fprintf(cgiOut,"<style type=\"text/css\">\n");
	fprintf(cgiOut,"body{background-image:url(../image/main.jpg);background-repeat:no-repeat;background-position:center}\n");
	fprintf(cgiOut,"</style>\n");

	fprintf(cgiOut, "<body backgroud=\">");
	fprintf(cgiOut, "<H1 align=\"center\"><b><font face=\"华文行楷\" color=\"#482D26\" size=\"+2\" >历史照片: </b></H1>");

	if(dir != NULL)
		{
			while((dirp = readdir(dir))  != NULL)
			{
			if(dirp->d_name[0] == '.') continue;//去 除隐藏 文件
			fprintf(cgiOut, "<div align=\"center\">");
			fprintf(cgiOut,"%s",dirp->d_name);
			fprintf(cgiOut, "</div>");
			
			//在 网页上 显示图片 
			fprintf(cgiOut, "<div align=\"center\"><img src=\"../motion/photo/%s\" width=\"320\" height=\"240\" />",dirp->d_name);
		//	fprintf(cgiOut, "<div align=\"center\"><img src=\"../images/%s\" width=\"320\" height=\"240\" />",dirp->d_name);
			fprintf(cgiOut, "</div>");
			
		}
	}
	fprintf(cgiOut, "</BODY></HTML>");
	return 0;
}
