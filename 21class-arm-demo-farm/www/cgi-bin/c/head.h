
#ifndef __HEAD_H
#define __HEAD_H

typedef struct {

	float tem_tm;
	float hum_tm;
	float ill_tm;
	float lev_tm;
	float sun_tm;
}shm_t;


typedef struct{
        int tem_st_hight;
        int tem_st_low;
        int tm_flag;
        int hum_st_high;
        int hum_st_low;
        int hum_flag;
//      int soil_st_high;
//      int soil_st_low;
//      int soil_flag;
        int sun_st_high;
        int sun_st_low;
        int sun_flag;
        int led_flag;
        int tou_flag;
}shm_s;



#endif
