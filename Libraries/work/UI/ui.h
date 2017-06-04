#ifndef _UI_H_
#define _UI_H_
#include "includes.h"
#include "app.h"
#include "oled.h"
#include "KEY.h"
#include "ctrl.h"
//#include "FlashUI.h"
/*******��������*******/
extern u8 (*FunctionPointer[11])(void);   //ָ�뺯��

extern int tingche;                  //ͣ����־λ
extern int speedswitch;                //�������
#define Menu_UI_ID               0
#define Run_UI_ID                1
#define State_UI_ID              2
#define Set_UI_ID                3
#define Record_UI_ID             4
#define Read_UI_ID               5

/*******��������*******/

u8 UI_Menu(void);      //������
u8 UI_Star(void);      //����
u8 UI_PID(void);       //��ʾPID��������
u8 UI_State(void);     //��ʾС��״̬����
u8 UI_Flash(void);  //��ʾ����A
u8 UI_Scheme_B(void);  //��ʾ����B


u8 Menu_UI(void); //  ������ IDΪ0
u8 Run_UI(void);  //  ���ܽ��� IDΪ1
u8 State_UI(void); //  �鿴��ͷ״̬���� IDΪ2
u8 Set_UI(void);   //  �������ý��� IDΪ3
u8 Record_UI(void); // ����������� IDΪ4
u8 Read_UI(void); //IDΪ5
void AddNumString(u8 ss[],u8 n[]);//���ּ�����ʾ�ַ���
void speedClear(void);            //������ �ص���ʼ״̬
#endif

