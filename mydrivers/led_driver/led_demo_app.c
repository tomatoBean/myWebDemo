#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>



#define LED_MAGIC 'L'

#define LED_ON  _IOW(LED_MAGIC, 0, int)
#define LED_OFF _IOW(LED_MAGIC, 1, int)



int main(int argc, char *argv[])
{
	int fd;
	int ret;

	fd = open("/dev/led_demo",O_RDWR);
	if (fd < 0)
	{
		printf(" open /dev/led_demo fail!!!\n");
		return -1;
	}

	while(1)
	{
		 ioctl(fd,LED_ON);
		 usleep(100000);
		 ioctl(fd,LED_OFF);
		 usleep(100000);
	}	
}
