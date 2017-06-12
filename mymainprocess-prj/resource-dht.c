#include"resources.h"


/*************************串口信息初始化*****************************************/
void uart_init(int fd)
{
	struct termios options;

	tcgetattr(fd, &options);
	

	options.c_cflag |= (CLOCAL | CREAD);//忽略所有调制解调器的状态行|启用字符接收器
	options.c_cflag &= ~PARENB;
	options.c_cflag &= ~CSIZE;  //字符长度
	options.c_cflag &= ~CRTSCTS; //使用RTS/CTS流控制
	options.c_cflag |= CS8;//发送或接收字符时使用8比特
	options.c_cflag &= ~CSTOPB; //一位停止位
	options.c_iflag |= IGNPAR;  // 忽略奇偶校验错误的字符
	options.c_iflag &= ~(BRKINT | INPCK | ISTRIP | ICRNL | IXON);
	options.c_cc[VTIME] = 0;  //非标准模式，TIME值
	options.c_cc[VMIN] = 1;  //非标准模式，MIN值

	tcflush(fd,TCIOFLUSH);
	options.c_oflag = 0; //输出模式
	options.c_lflag = 0;  // 本地模式

	cfsetispeed(&options, B115200);//设置波特率
	cfsetospeed(&options, B115200);

	tcsetattr(fd,TCSANOW,&options); 

	printf("uart ok!\n");    
}


void *dht_fun()
{
	char buf[4]={0};    // 接收温湿度
	char buff[5]={0};   // 接收烟雾值
	int temp;           //温湿度中间变量
	char flag=0;          //接收的类型区别
	char hc_temp;       //人体感应的中间变量
    int  mq_temp;       //烟雾值的中间变量
	char hc;
	/*************************cgi没有传递的初始数据******************************/
	mbuf[0] = 50;         //温度上限
	mbuf[1] = 0;          //温度下限
	mbuf[2] = 90;         //湿度上限
	mbuf[3] = 20;         //湿度下限
	mbuf[4] = 10000;      //烟雾上限
	/***************************************************************************/
	fd_dht = open("/dev/ttyUSB0",O_RDWR);
	if(fd_dht<2)
	{
		perror("open dht fail");
	}
	int i=0;
	uart_init(fd_dht);
	while(1)
	{
	//	printf("***********\n");
		read(fd_dht,&flag,sizeof(char));
		usleep(250000);
//		printf("flag = %d\n",flag);  //调试信息 打印的flag的值
	//	printf("#############\n");
		usleep(250000);
		switch((int)flag)
		{
		case TMP:
			read(fd_dht,&buf[0],sizeof(char));
			usleep(250000);
			read(fd_dht,&buf[1],sizeof(char));
			usleep(250000);
			read(fd_dht,&buf[2],sizeof(char));
			usleep(250000);
			read(fd_dht,&buf[3],sizeof(char));
			usleep(250000);
#if 0
			for(i=0;i<4;i++)
			{
				buf[i]=buf[i]-0x30;
			}
#endif
			shm->tmp = buf[0]*10+buf[1];
			shm->water = buf[2]*10+buf[3];
			printf("tmp = %d, water =%d\n",shm->tmp,shm->water);
#if 0
			for(i=0;i<4;i++)
			{
				printf("mbuf[%d]=%d\n",i,mbuf[i]);
			}
#endif
#if 1
			while(shm->tmp <  mbuf[1]|| shm->tmp >mbuf[0] || 
					shm->water < mbuf[3] || shm->water > mbuf[2])  //超出阈值范围 警报 蜂鸣器响五秒
			{
				while(i<5)
				{
					ioctl(fd_beep,PWM_ON);
					sleep(1);
					ioctl(fd_beep,PWM_OFF);
					sleep(1);
					i++;
				}
				i=0;
				break;
			}
			break;
#endif
		case HC_SR:
			read(fd_dht,&hc_temp,sizeof(char));
			usleep(250000);
			shm->hc = hc_temp ;
	//		shm->hc = hc_temp - 0x30;
			printf("hc_temp = %d\n",shm->hc);
			break;
		case MQ_2:
			read(fd_dht,&buff[0],sizeof(char));
			usleep(250000);
			read(fd_dht,&buff[1],sizeof(char));
			usleep(250000);
			read(fd_dht,&buff[2],sizeof(char));
			usleep(250000);
			read(fd_dht,&buff[3],sizeof(char));
			usleep(250000);
			read(fd_dht,&buff[4],sizeof(char));
			usleep(250000);
#if 0
			for(i=0;i<5;i++)
			{
				buff[i]= buff[i]-0x30;
			}
#endif
			mq_temp=buff[0]*10000+buff[1]*1000+buff[2]*100+buff[3]*10+buff[4];
			shm->mq = (mq_temp/5);
			printf("mq = %d\n",shm->mq);
#if 1
			while(shm->mq > mbuf[4])    // 烟雾值 超出阈值范围 灯闪烁五次
			{
				while(i<5)
				{
					ioctl(fd_led,TINY_LED_ON);
					sleep(1);
					ioctl(fd_led,TINY_LED_OFF);
					sleep(1);
					i++;
				}
				i=0;
				break;
			}
#endif
		default:
			break;
		}
		memset(buf,0,sizeof(buf));
		memset(buff,0,sizeof(buff));
	}
}
