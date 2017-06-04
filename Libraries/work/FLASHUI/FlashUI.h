#ifndef __FLASHUI_H__
#define __FLASHUI_H__


#include <stdint.h>
#include <includes.h>
//#include "ctrl.h"

#define     FLASH_SECTOR_SIZE       (2*1024)                //������С Ϊ 2k �ֽ�
#define     FLASH_SECTOR_NUM        (256)                   //������
#define     SECTOR_NUM  (FLASH_SECTOR_NUM-1)         //������������������ȷ����ȫ
#define     FLASH_ALIGN_ADDR        4                       //��ַ����������
typedef     uint32_t                  FLASH_WRITE_TYPE;       //flash_write ����д�� ����������
#define flash_read(sectorNo,offset,type)        (*(type *)((u32)(((sectorNo)*FLASH_SECTOR_SIZE) + (offset)))) 
      
#define SECTOR_NUM (FLASH_SECTOR_NUM-1) 

typedef struct pid
{
  float p;
	float i;
	float d;
}PID;

typedef struct stree_vim_pid_
{
   float  Kp_1;
   float  Kp_2;
   float  Kp_3;
   float  Kp_4;
   float  Kp_5;

   float  Kd_1;
   float  Kd_2;
   float  Kd_3;
   float  Kd_4;
   float  Kd_5;

}VIM_PID;

void Flash_Read(void);
void Falsh_Reserve(void);
void Falsh_Reserve_Head(void); 
void Flash_Read_Head(void); 
extern u8 flash_write(u16 sector_num,u16 offset,FLASH_WRITE_TYPE data);
extern void flash_init(void);
extern u8 flash_erase_sector(u16 sector_num);



#endif




































