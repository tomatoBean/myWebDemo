#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include "pwmhead.h"

int main()
{
	int i = 0;
	int n = 2;
	int dev_fd;
	int div;
	int pre = 255;
	dev_fd = open("/dev/mypwm",O_RDWR | O_NONBLOCK);
	if ( dev_fd == -1 ) {
		perror("open");
		exit(1);
	}
	while(1)
	{
		ioctl(dev_fd,PWM_ON);
		sleep(3);
		ioctl(dev_fd,PWM_OFF);
		sleep(2);
	}
}
