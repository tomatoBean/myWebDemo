CC = arm-none-linux-gnueabi-gcc
#CC = gcc
resource:
	$(CC) resource-mgr.c -o resource-mgr -lpthread
	sudo cp resource-mgr /rootfs/usr/sbin
clean:
	rm resource-mgr
.PHONY:clean resource
