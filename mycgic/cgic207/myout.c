#include <stdio.h>
#include "cgic.h"
#include <string.h>
#include <stdlib.h>
   
extern char *cgiQueryString;

int cgiMain() {

       cgiHeaderContentType("text/html");

       fprintf(cgiOut, "<HTML><HEAD>\n");
       fprintf(cgiOut, "<TITLE>My CGIC</TITLE></HEAD>\n");
       fprintf(cgiOut, "<BODY>");
       fprintf(cgiOut, "<H1>%s</H1>",cgiQueryString);
       fprintf(cgiOut, "</BODY>\n");
       fprintf(cgiOut, "</HTML>\n");

       return 0;
}
