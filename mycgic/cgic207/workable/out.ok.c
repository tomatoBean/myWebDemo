#include"cgic.h"
#include <stdio.h>

int cgiMain()
{	
	
        char name[241];
        char number[241];

	cgiHeaderContentType("text/html\n\n");

        fprintf(cgiOut, "<HTML><HEAD>\n");
        fprintf(cgiOut, "<TITLE>My CGI</TITLE></HEAD>\n");

        fprintf(cgiOut, "<BODY>");

        cgiFormString("name", name, 241);
        cgiFormString("number", number, 241);

    fprintf(cgiOut, "<H1>%s</H1>",name);
    fprintf(cgiOut, "<H1>%s</H1>",number);

	fprintf(cgiOut,"<H1>open fengxian success!</H1>");

	fprintf(cgiOut,"</BODY>\n");
	fprintf(cgiOut,"</HTML>\n");
		
	return 0;
}

