#include "includes.h"
#include "FlashUI.h"
#include "flash.h"
//#include "ctrl.h"

VIM_PID  stree_vim_pid;
PID streepid;       //ת��pid
PID speedpid;       //�ٶ�pid
PID linepid;        //ֱ��pid
int speed;          //�ٶ�

#define FTF    FTFL
#define PGM4      0x06  /* program phase program 4 byte */
#define ERSSCR    0x09  /* erase flash sector */
/*!
 *  @brief      Flash����
 *  @return     ����ִ�н��(1�ɹ���0ʧ��)
 *  @since      v5.0
 */
static inline u8 flash_cmd(){

	FTF->FSTAT = (0
                    |  FTFL_FSTAT_CCIF_MASK        // ָ����ɱ�־(д1��0)
                    |  FTFL_FSTAT_RDCOLERR_MASK    // ����ͻ�����־(д1��0)
                    |  FTFL_FSTAT_ACCERR_MASK      // ���ʴ����־λ(д1��0)
                    |  FTFL_FSTAT_FPVIOL_MASK      // �Ƿ����ʱ�����־λ(д1��0)
                  );
	while(!(FTF->FSTAT & FTFL_FSTAT_CCIF_MASK));  
	
	// �������־
    if( FTF->FSTAT & (FTFL_FSTAT_ACCERR_MASK | FTFL_FSTAT_RDCOLERR_MASK | FTFL_FSTAT_FPVIOL_MASK | FTFL_FSTAT_MGSTAT0_MASK))
    {
        return 0 ;                                  //ִ���������
    }
    else
    {
        return 1;                                   //ִ������ɹ�
    }


}


/*!
 *  @brief      д�볤�ֽ����ݵ� flashָ����ַ
 *  @param      sector_num      �����ţ�0 ~ FLASH_SECTOR_NUM��
 *  @param      offset          д�������ڲ�ƫ�Ƶ�ַ��0~2043 �� 4�ı�����
 *  @param      data            ��Ҫд�������
 *  @return     ִ�н��(1�ɹ���0ʧ��)
 *  @since      
 *  Sample usage:       flash_write(SECTOR_NUM,0,12);        //����255,ƫ�Ƶ�ַΪ0,д������:12
 */
u8 flash_write(u16 sector_num,u16 offset,FLASH_WRITE_TYPE data)
{

	u16 ret;
	u32 addr = sector_num * FLASH_SECTOR_SIZE + offset;
	u32 tmpdata;
	typedef union
	{
		uint32_t  word;
		uint8_t   byte[4];
	} dest;
//	ASSERT(offset % FLASH_ALIGN_ADDR == 0);             //ƫ��������Ϊ4�ı���
//    //�˴���ʾ���棬���ǰ�ȫ�ġ���
//    ASSERT(offset <= FLASH_SECTOR_SIZE);                //������СΪ2K����ƫ�������벻���� 0x800
//    //�˴���ʾ���棬���ǰ�ȫ�ġ���
	//����Ŀ���ַ
	FTF->FCCOB1 = ((dest *)&addr)->byte[2];
	FTF->FCCOB2 = ((dest *)&addr)->byte[1];
	FTF->FCCOB3 = ((dest *)&addr)->byte[0];
	
	//���õ�32Ϊ����
	tmpdata = (u32)data;
	FTF->FCCOB4 = ((dest *)&tmpdata)->byte[3];
	FTF->FCCOB5 = ((dest *)&tmpdata)->byte[2];
	FTF->FCCOB6 = ((dest *)&tmpdata)->byte[1];
	FTF->FCCOB7 = ((dest *)&tmpdata)->byte[0];
	
	 // ���ò�������
    FTF->FCCOB0 = PGM4;
	
	 __disable_irq();   //��ֹ�ж�
    ret =  flash_cmd();    
    __enable_irq();     //�����ж�
	
	if(ret ==0)
	{
		return 0;
	}
	return 1;
}


/*!
 *  @brief      ����ָ��flash����
 *  @param      sector_num    �����ţ�K60N512ʵ��ʹ��0~255��
 *  @return     ִ�н��(1�ɹ���0ʧ��)
 *  @since      v5.0
 *  Sample usage:       flash_erase_sector(127);        //��������127
 */
u8 flash_erase_sector(u16 sector_num)
{
	typedef union
	{
		uint32_t  word;
		uint8_t   byte[4];
	} dest;
	u32 addr = sector_num * FLASH_SECTOR_SIZE;
	/* set cmd */
	FTF->FCCOB0 = ERSSCR; 
	FTF->FCCOB1 = ((dest *)&addr)->byte[2];
	FTF->FCCOB2 = ((dest *)&addr)->byte[1];
	FTF->FCCOB3 = ((dest *)&addr)->byte[0];
	
	if(flash_cmd() == 0)
    {
        return 0;
    }

    if(sector_num == 0)
    {
        return flash_write(sector_num,0x00040C,0xFFFFFFFE);
    }

    return 1;
}



void Falsh_Reserve() 
{
  flash_erase_sector(SECTOR_NUM); 
  flash_write(SECTOR_NUM, 0,(u32)(speedpid.p*10));
	flash_write(SECTOR_NUM, 4,(u32)(speedpid.i*10));
  flash_write(SECTOR_NUM, 8,(u32)(speedpid.d*10));
	
// flash_write(SECTOR_NUM, 12,(u32)(linepid.p*10));     //֪��pid
//  flash_write(SECTOR_NUM, 16,(u32)(linepid.i*10));   
//	flash_write(SECTOR_NUM, 20,(u32)(linepid.d*10));
//	
//  flash_write(SECTOR_NUM, 24,(u32)(speedpid.p*10));  
//  flash_write(SECTOR_NUM, 28,(u32)(speedpid.i*10));  
//  flash_write(SECTOR_NUM, 32,(u32)(speedpid.d*10));  
//  flash_write(SECTOR_NUM, 36,(u32)speed);  
	
	flash_write(SECTOR_NUM, 12,(u32)(streepid.p*10));  
  flash_write(SECTOR_NUM, 16,(u32)(streepid.i*10));  
  flash_write(SECTOR_NUM, 20,(u32)(streepid.d*10));  
  flash_write(SECTOR_NUM, 24,(u32)speed);  

}

void Flash_Read()  
{
  speedpid.p=((float)(flash_read(SECTOR_NUM, 0, u32)))/10;
  speedpid.i=((float)(flash_read(SECTOR_NUM, 4, u32)))/10;
  speedpid.d=((float)(flash_read(SECTOR_NUM, 8, u32)))/10;
	
  streepid.p=((float)(flash_read(SECTOR_NUM, 12, u32)))/10;
  streepid.i=((float)(flash_read(SECTOR_NUM, 16, u32)))/10;
  streepid.d=((float)(flash_read(SECTOR_NUM, 20, u32)))/10;
//	
//	linepid.p=((float)(flash_read(SECTOR_NUM, 24, u32)))/10;
//  linepid.i=((float)(flash_read(SECTOR_NUM, 28, u32)))/10;
//  linepid.d=((float)(flash_read(SECTOR_NUM, 32, u32)))/10;
//  speed=flash_read(SECTOR_NUM, 36, u32);
	
	speed=flash_read(SECTOR_NUM, 24, u32);

//  stree_vim_pid.Kp_3=((float)(flash_read(SECTOR_NUM, 48, u32)))/10;
//  stree_vim_pid.Kp_4=((float)(flash_read(SECTOR_NUM, 52, u32)))/10;
//  stree_vim_pid.Kp_5=((float)(flash_read(SECTOR_NUM, 56, u32)))/10;
//  missLine= ((float)(flash_read(SECTOR_NUM, 48, u32)));
//  missLine_M= ((float)(flash_read(SECTOR_NUM, 52, u32)));
}





