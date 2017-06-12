https://www.w3.org/standards/
https://www.w3.org/standards/webdesign/htmlcss
https://boutell.com/cgic/
http://www.cgi101.com/book/ch1/text.html
http://www.w3school.com.cn/tags/tag_form.asp
http://www.boa.org/documentation/boa-1.html
https://httpd.apache.org/

git clone https://github.com/boutell/cgic

-------------------------------------------------------
=======================================================================

[ code download ]

  https://github.com/Akagi201/boa

[ compile  ]
  ./configure
   make

[ installation ]
    sudo mkdir /var/www
            index.html
    sudo mkdir /etc/boa
            boa.conf
    sudo mkdir /var/log/boa

It is easy to compile and run on x86 platform.

--------------------------------------------------------------------
--------------------------------------------------------------------

[ porting to Linux ]

   ./configure  --host=arm-none-linux-gnueabi
   make
   sudo mkdir /rootfs/var/www
        put index.html
   sudo mkdir /etc/boa
       put boa.conf but it needs to modify from "nobody" to 0
   sudo mkdir /var/log/boa
   Compared with x86 platform, only boa.conf file needs to be modified.

[ careful configurations  ]
   
   to see  ----  /etc/boa/boa.conf
  
   item1:
        User 0
        Group 0

     item2:
         ScriptAlias /cgi-bin/ /var/www/cgi-bin/

     item3:
          DocumentRoot /var/www

     item4:
          DirectoryIndex index.html

[ logic of teachings ]

      test.html
      mytest.c --> mytest.cgi
      cgictest.c --> cgictest.cgi


[ phenomena  ]

beep --> device node ---> main process(head file for ioctl commands) ----> beep.cgi(head file for ioctl commands)
 key_m = ftok("/www/cgi-bin/",'m');// ------->/var/www/cgi-bin/ (both cgi and main process)


502 Bad Gateway  
The CGI was not CGI/1.1 compliant

fake  phenomena:    
printf("Content-type: text/html");  ----->  printf("Content- type: text/html\n\n");

true phenomena:
   boa.conf

board operations:
--> insmod pwmdriver.ko
--> video_main
--> /usr/sbin/boa

[ demo procedures for students  ]
     hello-1.html(post)
     hello-2.html(get)
     hello-3.html(cgictest)
     farsight

     real-project:
     
      index.html    --->  main interface;
      register.html --->  interface for registering new user 
      main.html     --->  main control interface;
      
      video.html   ---> sub interface for real-time monitoring
      picture.html ---> sub interface for history pictures
      monitor.html ---> sub interface for video recording

      index.html ----> any button -----> login.cgi --- login button --- existed? -----> YES ----> "Login Success" -----> main.html
                                            |                               |     
                                            |                               NO
					    |                               |	
   register.cgi                     register button                      "error"
          |                                 |                               |
   register.html<----- "jump to ..."  <---- |                               |   
                                                                            |
===========================================================                 |
                                                                           index.html(to come back) 
     sqlite topic

---------------------------------

 how to test sqlite3 ?
  to quit sqlite shell:   ctrl + d

   sqlite3 usr.db

  .quit
  .help
  .tables
  .databases ----> print names of database file
  .show   ------> print environment variables
   ".schema"命令，在没有参数的情况，它会显示最初用于创建数据库的CREATE TABLE和CREATE INDEX的SQL语句。

   to create table:   create table user(name varchar(255),passwd varchar(255));
   to insert table:   insert into user values('tomato','123');
   to see table values:   select * from  user;

sql language practise:
    select * from user where name ='fengxianl';

    insert into user values('eric','123456',50,10,20,90,10000);


     html topic
---------------------------------

主要介绍 input、select、textarea、label、fieldset、ul、ol、li等标签.

meta标签的http-equiv属性语法格式是：
<meta http-equiv="参数"  content="参数变量值">；

http-equiv顾名思义，相当于http的文件头作用，它可以向浏览器传回一些有用的信息，以帮助正确和精确地显示网页内容，
与之对应的属性值为content，content中的内容其实就是各个参数的变量值。


其中http-equiv属性主要有以下几种参数：

A、Expires(期限)

	说明：可以用于设定网页的到期时间。一旦网页过期，必须到服务器上重新传输。

	用法：<metahttp-equiv="expires"content="Fri,12Jan200118:18:18GMT">

	注意：必须使用GMT的时间格式。

B、Pragma(cache模式)

	说明：禁止浏览器从本地计算机的缓存中访问页面内容。

	用法：<metahttp-equiv="Pragma"content="no-cache">

	注意：这样设定，访问者将无法脱机浏览。

C、Refresh(刷新)

	说明：自动刷新并指向新页面。

	用法：<meta http-equiv="Refresh" content="2; URL=http://www.jb51.net">(注意后面的引号，分别在秒数的前面和网址的后面)

	注意：其中的2是指停留2秒钟后自动刷新到URL网址。

D、Set-Cookie(cookie设定)

说明：如果网页过期，那么存盘的cookie将被删除。

用法：<metahttp-equiv="Set-Cookie"content="cookievalue=xxx;expires=Friday,12-Jan-200118:18:18GMT；path=/">

注意：必须使用GMT的时间格式。

E、Window-target(显示窗口的设定)

说明：强制页面在当前窗口以独立页面显示。

用法：<metahttp-equiv="Window-target"content="_top">

注意：用来防止别人在框架里调用自己的页面。

F、content-Type(显示字符集的设定)

说明：设定页面使用的字符集。

用法：<metahttp-equiv="content-Type"content="text/html;charset=gb2312">

G、content-Language（显示语言的设定）

用法：<metahttp-equiv="Content-Language"content="zh-cn"/>

H、Cache-Control指定请求和响应遵循的缓存机制。
Cache-Control指定请求和响应遵循的缓存机制。在请求消息或响应消息中设置Cache-Control并不会修改另一个消息处理过程中的缓存处理过程。

