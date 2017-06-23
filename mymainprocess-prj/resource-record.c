#include "resources.h"

void *record_fun()
{
	int cmd;

	printf("###ENTER RECORDING THREAD...");
	while(1)
	{
		pthread_mutex_lock(&mutex_record);
		pthread_cond_wait(&cond_record,&mutex_record);  
		cmd = msg.cmd;
		pthread_mutex_unlock(&mutex_record);
		switch(cmd)
		{
		case RECORD_ON:
 			printf("###To begin with recording...\n");
                	system("killall mjpg_streamer");
                	usleep(500);
                	system("ffmpeg  -f video4linux2 -s 320*240 -r 10 -i /dev/video0  /motion/photo/videoR.avi &");
			break;

		case RECORD_OFF:
 			printf("###To end with recording...\n");
                	system("killall ffmpeg");
                	usleep(1000000);
                	system("mjpg_streamer -i \"/mjpg/input_uvc.so -y\" -o \"/mjpg/output_http.so -w /www\" &");
			break;
		case RECORD_DEL:
			system("rm -rf /var/www/motion/photo/*.jpg");
			break;
		case RECORD_RESET:
                	system("killall mjpg_streamer");
                	system("killall ffmpeg");
                	usleep(1000000);
                	system("mjpg_streamer -i \"/mjpg/input_uvc.so -y\" -o \"/mjpg/output_http.so -w /www\" &");
			break;
		default:
			break;
		}
	}
	pthread_exit(NULL);
}
