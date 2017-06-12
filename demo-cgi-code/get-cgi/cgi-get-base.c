#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cgic.h"
#include "cgic.c"


/*

Get请求就是我们在浏览器地址栏输入URL时发送请求的方式，或者我们在HTML中定义一个表单（form）时，把action属性设为“Get”时的工作方式；

	Get请求字符串就是跟在URL后面以问号“?”开始的字符串，但不包括问号。比如这样的一个请求：
		http://127.0.0.1/cgi-bin/out.cgi?ThisIsTheGetString

	在上面这个URL中，“ThisIsTheGetString”就是Get请求字符串。


http://www.cgi101.com/book/ch3/text.html

*/


extern char *cgiQueryString;

int cgiMain() {

    cgiHeaderContentType("text/html");

    fprintf(cgiOut, "<HTML><HEAD>/n");
    fprintf(cgiOut, "<TITLE>My CGIC</TITLE></HEAD>/n");

    fprintf(cgiOut, "<BODY>");
    fprintf(cgiOut, "<H1>%s</H1>",cgiQueryString);
    fprintf(cgiOut, "</BODY>/n");
    fprintf(cgiOut, "</HTML>/n");

    return 0;
}
