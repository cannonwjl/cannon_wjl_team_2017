#include "pwm.h"
//#include "includes.h"

//����������Ƶ�ʸ�150��������

void speedInit()
{
	FTM_PWM_QuickInit(FTM0_CH3_PC04,kPWM_EdgeAligned,10000);    //���
	FTM_PWM_QuickInit(FTM0_CH2_PC03,kPWM_EdgeAligned,10000);    //���
  FTM_PWM_QuickInit(FTM1_CH1_PA09,kPWM_EdgeAligned,300);      //���
	FTM_PWM_ChangeDuty(HW_FTM0, HW_FTM_CH3, 0);
	FTM_PWM_ChangeDuty(HW_FTM0, HW_FTM_CH2, 0);
	FTM_PWM_ChangeDuty(HW_FTM1, HW_FTM_CH1, 2000);

}