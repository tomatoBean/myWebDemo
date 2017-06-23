#include "resources.h"

void *snapshot_fun()
{
	int cmd;

	printf("###ENTER SNAPSHOT THREAD...");
	while(1)
	{
		pthread_mutex_lock(&mutex_snapshot);
		pthread_cond_wait(&cond_snapshot,&mutex_snapshot);  
		cmd = msg.cmd;
		pthread_mutex_unlock(&mutex_snapshot);
		switch(cmd)
		{
		case SNAPSHOT_ON:
  			printf("###To begin with snapshot...\n");
                	system("killall mjpg_streamer");
                	usleep(500);
                	system("killall ffmpeg");
                	usleep(500);
                	system("mjpg_streamer -i \"/mjpg/input_uvc.so -y\" -o \"/mjpg/output_http.so –w /www\" -o \"/mjpg/output_file.so -f /var/www/motion/photo -d 1000\" &");
			break;

		case SNAPSHOT_OFF:
   			printf("###To end with snapshot...\n");
                	system("killall mjpg_streamer");
                	usleep(500);
                	system("killall ffmpeg");
                	usleep(1000000);
                	system("mjpg_streamer -i \"/mjpg/input_uvc.so -y\" -o \"/mjpg/output_http.so -w /www\" &");
			//mjpg_streamer -i "/mjpg/input_uvc.so -y" -o "/mjpg/output_http.so -w /www" &
			break;
		case SNAPSHOT_DEL:
			system("rm -rf /var/www/motion/photo/*.jpg");
			break;
		default:
			break;
		}
	}
	pthread_exit(NULL);
}
