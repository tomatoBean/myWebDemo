void zigbee_serial_init(int fd)
{
    struct termios options;
    
	tcgetattr(fd, &options);  //用于获取与终端相关的参数
	options.c_cflag |= (CLOCAL | CREAD);//忽略所有调制解调器的状态行|启用字符接收器
	options.c_cflag &= ~CSIZE;  //字符长度
	options.c_cflag &= ~CRTSCTS; //使用RTS/CTS流控制
	options.c_cflag |= CS8;//发送或接收字符时使用8比特
	options.c_cflag &= ~CSTOPB; //每个字符使用两停止位
	options.c_iflag |= IGNPAR;  // 忽略奇偶校验错误的字符
	options.c_iflag &= ~(BRKINT | INPCK | ISTRIP | ICRNL | IXON);
    //在当前输入行中检测到一个终止状态时，产生一个中断 |对接收的字符执行奇偶校验
	// |将所有接收的字符裁减为7比特 | 将接收到的新的回车符转换为换行符 | 对输出启用软件流控制
	
    //options.c_cc[VTIME] = 2;  //非标准模式，TIME值
    options.c_cc[VMIN] = 12;  //非标准模式，MIN值
    
	options.c_oflag = 0; //输出模式
	options.c_lflag = 0;  // 本地模式

	cfsetispeed(&options, B115200);//设置波特率
	cfsetospeed(&options, B115200);
    
	tcsetattr(fd,TCSANOW,&options); // 用于设置终端函数参数，TCSANOW:立刻对值进行修改

    printf("zigbee serial ok!\n");
    
}
