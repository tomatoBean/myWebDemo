#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cgic.h"
#include "cgic.c"

int cgiMain() { // cgiMain() 调用不同的函数 . 当函数结束后 , 将返回 0 

   // 在输出文挡之前简要说明 MIME type , 如 "text/html"
   /* Important: we must indicate the type of document */ 

  // 这个语句的调用一定要在所有printf 语句之前。而这个语句执行的任务实际上就是：
  //  void cgiHeaderContentType(char *mimeType) {
  //  		fprintf(cgiOut, "Content-type: %s\r\n\r\n", mimeType);
  //  }

// MIME type的缩写为(Multipurpose Internet Mail Extensions)代表互联网媒体类型(Internet media type)，MIME使用一个简单的字符串组成，最初是为了标识邮件Email附件的类型，在html文件中可以使用content-type属性表示，描述了文件类型的互联网标准。
// MIME类型能包含视频、图像、文本、音频、应用程序等数据。

     cgiHeaderContentType("text/html");

     fprintf(cgiOut, "<HTML><HEAD>\n");
     fprintf(cgiOut, "<TITLE>My First CGI</TITLE></HEAD>\n");

     fprintf(cgiOut, "<BODY><H1>Hello CGIC</H1></BODY>\n");

     fprintf(cgiOut, "</HTML>\n");

     return 0;
}
