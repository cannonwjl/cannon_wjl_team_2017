#include "KEY.h"

/******������ʼ��*******/
void KEY_Init()
{
  GPIO_QuickInit(HW_GPIOA,12, kGPIO_Mode_IPU );          //��ʼ�� PTE0 �ܽţ����ù���ΪGPIO ���½��ش����жϣ���������
  GPIO_QuickInit(HW_GPIOA,11, kGPIO_Mode_IPU );          //��ʼ�� PTE2 �ܽţ����ù���ΪGPIO ���½��ش����жϣ���������
  GPIO_QuickInit(HW_GPIOA,13, kGPIO_Mode_IPU );          //��ʼ�� PTE4 �ܽţ����ù���ΪGPIO ���½��ش����жϣ���������
  GPIO_QuickInit(HW_GPIOA,14, kGPIO_Mode_IPU );          //��ʼ�� PTE6 �ܽţ����ù���ΪGPIO ���½��ش����жϣ���������
	GPIO_QuickInit(HW_GPIOA,10, kGPIO_Mode_IPU );          //��ʼ�� PTE6 �ܽţ����ù���ΪGPIO ���½��ش����жϣ���������
	//GPIO_QuickInit(HW_GPIOA,29, kGPIO_Mode_IPU );          //�ɻɹ�
}


u8 key_check(u8 key)
{
    
    if(PAin(key))
    {
        OSTimeDly(0);
        if(PAin(key))
        {
            return 0;
        }
    }
    return 1;
}







