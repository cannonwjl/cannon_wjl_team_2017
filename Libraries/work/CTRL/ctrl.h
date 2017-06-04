#ifndef CTRL_H_
#define CRTL_H_

#include "includes.h"

extern int result; 

#define  KPPLUSMAX      (190)
#define  KPNEGATIVEMAX  (-190)
#define  KIPLUSMAX      (190)
#define  KINEGATIVEMAX  (-190)
#define  KDPLUSMAX      (190)
#define  KDNEGATIVEMAX  (-190)
#define  KWPLUSMAX      (190)
#define  KWNEGATIVEMAX  (-190)
#define  KOUPLUSMAX     (5000)

//extern PID streepid;       //ת��pid
//extern PID speedpid;       //�ٶ�pid
//extern int speed;          //�ٶ�
//extern int ad1_value;              //ad1�˲����ֵ
//extern int ad2_value;              //ad2�˲����ֵ
//int ad1_value;             //ad1�˲����ֵ
//int ad2_value;              //ad2�˲����ֵ

void linePID(int nowValue);
void speedCtrl(void);
void speedPID(u32 nowValue);
void streePID(int nowValue);
void ctrl(void);
void guiyi_qian(void);
//void filter(void);
int Turn_speed(int sum_ad);
	
#endif
