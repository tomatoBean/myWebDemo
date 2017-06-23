CC=arm-none-linux-gnueabi-gcc
AFLAGS=-Wall -l sqlite3
OBJS=login.cgi ca_picture.cgi hs_picture.cgi ill_env.cgi tem_env.cgi hum_env.cgi lev_env.cgi register.cgi video.cgi

run:$(OBJS)

$(OBJS):%.cgi:%.c
	$(CC) $(AFLAGS) $<  -o $@
.PHONY:clean
	clean:
	rm *.cgi
