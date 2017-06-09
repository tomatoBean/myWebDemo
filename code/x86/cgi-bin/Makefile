#CC =arm-none-linux-gnueabi-gcc
CC  =gcc
log.cgi:
	$(CC) login.c -o login.cgi -I /home/linux/sqlite-3.7.3/sqlite-3.7.3/sqlite_install/include/ -L /home/linux/sqlite-3.7.3/sqlite-3.7.3/sqlite_install/lib/ -lsqlite3
#register.cgi:
	$(CC) register.c -o register.cgi -I /home/linux/sqlite-3.7.3/sqlite-3.7.3/sqlite_install/include/ -L /home/linux/sqlite-3.7.3/sqlite-3.7.3/sqlite_install/lib/ -lsqlite3
#setenv.cgi:
	$(CC) setenv.c -o setenv.cgi 
	#-I /home/linux/sqlite-3.7.3/sqlite-3.7.3/sqlite_install/include/ -L /home/linux/sqlite-3.7.3/sqlite-3.7.3/sqlite_install/lib/ -lsqlite3
#led.cgi:
	$(CC) led.c -o led.cgi
#beep.cgi:
	$(CC) beep.c -o beep.cgi
#temp.cgi:
	$(CC) temp.c -o temp.cgi
#humidity.cgi:
	$(CC) humidity.c -o humidity.cgi
#hc.cgi:
	$(CC) hc.c -o hc.cgi
#mq.cgi:
	$(CC) mq.c -o mq.cgi
	$(CC) picture.c -o picture.cgi
	$(CC) capture.c -o capture.cgi
	$(CC) video.c -o video.cgi
	$(CC) setenv.c -o setenv.cgi
clean:
	sudo rm -rf *.cgi
.PHONY:clean
