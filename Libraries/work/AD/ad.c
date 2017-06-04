#include "ad.h"
#include "common.h"

int max1,min1;
int max2,min2;
int sum_ad1,sum_ad2;   //��һ�����ֵ
int ad1;
int ad2;
int ad3;
int ad4;

int ad2_one=0,ad4_one=0;
float ad2_lv[10]={0,0,0,0,0,0,0,0,0,0};
float ad4_lv[10]={0,0,0,0,0,0,0,0,0,0};
int average1;
int average2;  //�˲����ֵ
//int sum1=0;
//int sum0=0;
int lv=0;   

char i=0;

int value_buf1[12]={0,0,0,0,0,0,0,0,0,0,0,0};
int value_buf2[12]={0,0,0,0,0,0,0,0,0,0,0,0};
int ad1_max;
int ad3_max;
int ad1_min=900;
int ad3_min=900;

float ad2_max;
float ad4_max;
float ad2_min=900;
float ad4_min=900;

float guiyi_ad1 = 0;
float guiyi_ad3 = 0;

//int ad3;
//int ad4;

void Init_AD(uint32_t instance)
{
	/* ��ʼ��ADCģ�� ADC0_SE19_BM0 */
    ADC_InitTypeDef ADC_InitStruct1;
    ADC_InitStruct1.instance = instance;
    ADC_InitStruct1.clockDiv = kADC_ClockDiv2; /* ADC����ʱ��2��Ƶ */
    ADC_InitStruct1.resolutionMode = kADC_SingleDiff12or13;
    ADC_InitStruct1.triggerMode = kADC_TriggerSoftware; /* �������ת�� */
    ADC_InitStruct1.singleOrDiffMode = kADC_Single; /*����ģʽ */
    ADC_InitStruct1.continueMode = kADC_ContinueConversionEnable; /* ��������ת�� ת��һ�κ� �Զ���ʼ��һ��ת��*/
    ADC_InitStruct1.hardwareAveMode = kADC_HardwareAverageDisable; /*��ֹ Ӳ��ƽ�� ���� */
    ADC_InitStruct1.vref = kADC_VoltageVREF;                       /* ʹ���ⲿVERFH VREFL ��Ϊģ���ѹ�ο� */
    ADC_Init(&ADC_InitStruct1);
    
    /* ��ʼ����Ӧ���� */
    /* DM0����Ϊר�ŵ�ģ������ ADCʱ �������ø���  DM0Ҳ�޷�������ͨ���������� */
    
    /* ����һ��ADCת�� */
//    ADC_StartConversion(HW_ADC0, 13, kADC_MuxA);     //PB3
//	  ADC_StartConversion(HW_ADC1, 10, kADC_MuxA);     //PB4
//	  ADC_StartConversion(HW_ADC1, 11, kADC_MuxA);     //PB5
//	  ADC_StartConversion(HW_ADC1, 12, kADC_MuxA);     //PB6
}

//����һ��adת��
int adc_once(uint32_t instance, uint32_t chl)
{
	ADC_StartConversion(instance, chl, kADC_MuxA);
  return ADC_ReadValue(instance, kADC_MuxA);
}

//int max_main(void)
//{
//	max
//}	


#define N 3
void filter(void)       //�˲�
{  
	  ad();
}
//*********************************************************************************//
//void ad(void)  ad�ɼ�����
//ad �ɼ�������ֵ   ����ֻ�õ���ad2  �� ad4��ֵ    2017-5-31
//���ɼ�������ֵ��ƽ������ʹ�䲻�������䣬���ǹ������ƽ���ή�ͷ�Ӧʱ�ٶȣ�˼·����

//��ڲ�������
//���ز�������

 //˵����

//�ҽ�������5��ƽ�� ���в���    ���û��Ӱ�����

//*********************************************************************************//
int avg_ad1[5],avg_ad2[5],avg_ad3[5],avg_ad4[5];
void ad(void)
{
	
	int d=0;
  float ad2_buf=0,ad4_buf=0;	
	float ad2_yuan=0,ad4_yuan=0;
	
		ADC_StartConversion(HW_ADC1, 4, kADC_MuxA);
	avg_ad1[0]=ADC_QuickReadValue(ADC1_SE4_PE0);
////	ad1=2000;
	ADC_StartConversion(HW_ADC1, 5, kADC_MuxA);
	avg_ad2[0]=ADC_QuickReadValue(ADC1_SE5_PE1);
	
	ADC_StartConversion(HW_ADC1, 6, kADC_MuxA);
	avg_ad3[0]=ADC_QuickReadValue(ADC1_SE6_PE2);
	
	ADC_StartConversion(HW_ADC1, 7, kADC_MuxA);
	 //ԭ����50  ��֪��Ϊʲô
	//ad4=ADC_QuickReadValue(ADC1_SE7_PE3)-50;
	avg_ad4[0]=ADC_QuickReadValue(ADC1_SE7_PE3);
	
	
	avg_ad1[4]=avg_ad1[3];
	avg_ad1[3]=avg_ad1[2];
	avg_ad1[2]=avg_ad1[1];
	avg_ad1[1]=avg_ad1[0];
	ad1=(avg_ad1[4]+avg_ad1[3]+avg_ad1[2]+avg_ad1[1]+avg_ad1[0])/5;
	      
	avg_ad2[4]=avg_ad2[3];
	avg_ad2[3]=avg_ad2[2];
	avg_ad2[2]=avg_ad2[1];
	avg_ad2[1]=avg_ad2[0];
	ad2=(avg_ad2[4]+avg_ad2[3]+avg_ad2[2]+avg_ad2[1]+avg_ad2[0])/5;
	
	avg_ad3[4]=avg_ad3[3];
	avg_ad3[3]=avg_ad3[2];
	avg_ad3[2]=avg_ad3[1];
	avg_ad3[1]=avg_ad3[0];
	ad3=(avg_ad3[4]+avg_ad3[3]+avg_ad3[2]+avg_ad3[1]+avg_ad3[0])/5;
	
	avg_ad4[4]=avg_ad4[3];
	avg_ad4[3]=avg_ad4[2];
	avg_ad4[2]=avg_ad4[1];
	avg_ad4[1]=avg_ad4[0];
	ad4=(avg_ad4[4]+avg_ad4[3]+avg_ad4[2]+avg_ad4[1]+avg_ad4[0])/5;
	
/******************�˲�1**********************************/	
//	if((ad2-ad2_one>=500)||(ad2-ad2_one<=-500))
//		ad2=ad2_one;
//	else
//		ad2_one=ad2;
//	if((ad4-ad4_one>=500)||(ad4-ad4_one<=-500))
//		ad4=ad4_one;
//	else
//		ad4_one=ad4;

/*****************�˲�2***********************************/

//    ad2_lv[lv]=ad2_yuan;
//	  ad4_lv[lv]=ad4_yuan;
//    lv++;
//  if(lv==4)
//	{
//		ad2_one=ad2_lv[0];
//		ad4_one=ad4_lv[0];
//		for(d=0;d<=lv;d++)
//		{
//			if(ad2_one<=ad2_lv[d])
//				ad2_one=ad2_lv[d];
//			
//			if(ad4_one<=ad4_lv[d])
//				ad4_one=ad4_lv[d];
//		}
//		
//		for(d=0;d<=(lv-1);d++)
//		{
//			ad2_buf=ad2_lv[d];
//			ad4_buf=ad4_lv[d];
//		}
//	  ad2=(int)((ad2_buf-ad2_one)/(lv-1));
//		ad4=(int)((ad4_buf-ad4_one)/(lv-1));
//		lv=0;
//	}
		

//	ad1=adc_once(HW_ADC1, 4);
//	ad2=adc_once(HW_ADC1, 13);
}

void guiyi(void)               //��һ��
{
//	u8 count;
	float value_buf1,value_buf3;
	int i=0;
	int sum;
  float sum1,sum3,sum4;
	
//	value_buf1[i]=ad1;
//	value_buf2[i]=ad2;
	  //2017-6-1   ��һ��˼��  
	  //��ռ�б��� ��������� ���߸��� �ж�  
	  // 
	//   sum=ad3+ad4;
	//   sum3=ad3/sum;
	//   sum4=ad4/sum;
	//  // 
	
  guiyi_ad3 = ((float)ad4/((float)ad4_max - (float)ad4_min))*800;
	guiyi_ad1 = ((float)ad3/((float)ad3_max - (float)ad3_min))*800;
	
//	if(i<6)
//	{
//		i++;
//		value_buf1+=sum1;
//		value_buf3+=sum3;
//	}
//  if(i==6)
//	{
//  guiyi_ad1=(float)(value_buf1/6);
//	guiyi_ad3=(float)(value_buf3/6);
//		value_buf1=0;
//		value_buf3=0;
//		i=0;
//	}
}

void max_min(void)
{
	if(ad3_max<=ad3)
	   ad3_max=ad3;
	
	if(ad4_max<=ad4)
	   ad4_max=ad4;
	
	if(ad3_min>=ad3)
	   ad3_min=ad3;
	
	if(ad4_min>=ad4)
	   ad4_min=ad4;
	
	
}