#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cgic.h"
#include "cgic.c"

int cgiMain() {

     cgiHeaderContentType("text/html");

     fprintf(cgiOut, "<HTML><HEAD>\n");
     fprintf(cgiOut, "<TITLE>My First CGI</TITLE></HEAD>\n");

     fprintf(cgiOut, "<BODY><H1>Hello CGIC</H1></BODY>\n");

     fprintf(cgiOut, "</HTML>\n");

     return 0;
}
