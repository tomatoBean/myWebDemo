#ifndef __PWMHEAD__
	#define __PWMHEAD__
	#define MAGIC     'p'
	#define PWM_ON    _IO(MAGIC,0)
	#define PWM_OFF   _IO(MAGIC,1)
#endif
