/************************************************************************************
//�����������������ҡ����Ա�����: https://shop149406681.taobao.com/?spm=a1z10.1-c.0.0.64cb457fKzgKea 
//�Ա����������ؼ��ʣ�K_A37_005
//  �� �� ��   : v1.0
//  ��    ��   : ����������
//  ����Ⱥ :			 1041406448�����������������ע���棩
//    CSDN  ��������������Դ�����б����н���˵����   :��Ƭ��������˹�(�����ؼ��ʣ�K_A37_005)
//    BILIBILI����ʾ��Ƶ�� :����������(�����ؼ��ʣ�K_A37_005)
//  ��������   : 2021-6-21
//  ����޸�   : 2021-11-21
//  ��������   : ADS1115����Գ���
//  ��������   : STM32F103C8T6   ����8M  ϵͳʱ��72M
����
ADS1115--------------------------------STM32F103C8T6
VCC-- ---------------------------------5V
GND- ----------------------------------GND
SCL- ----------------------------------PB_4 //SCL
SDA- ----------------------------------PB_3 //SDA	

OLED0.96
VCC-- ---------------------------------3.3V
GND- ----------------------------------GND
SCL- ----------------------------------PB_8 //SCL
SDA- ----------------------------------PB_9 //SDA	
*************************************************************************************/

#include "DS1302.h"
#include "delay.h"

//---DS1302д��Ͷ�ȡʱ����ĵ�ַ����---//
//---���ʱ�������� ���λ��дλ;-------//
uint8_t  READ_RTC_ADDR[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d}; 
uint8_t  WRITE_RTC_ADDR[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};

//---DS1302ʱ�ӳ�ʼ��2013��1��1�����ڶ�12��00��00�롣---//
//---�洢˳�������ʱ��������,�洢��ʽ����BCD��---//
uint8_t TIME[7] = {0x00, 0x47, 0x21, 0x29, 0x3, 0x03, 0x23};

/*******************************************************************************
���ó��������ģʽ
*******************************************************************************/
void DS1302_OUT_GPIO_INIT(void)
{

	GPIO_InitTypeDef  GPIO_InitStructure;  

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
 
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//
	GPIO_Init(GPIOA, &GPIO_InitStructure);

}
/*******************************************************************************
�����������ó���������ģʽ
*******************************************************************************/
void DS1302_IN_GPIO_INIT(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;  

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void Delay1us(void)
{
    DelayUs(1);
}
void Ds1302Write(uint8_t addr, uint8_t dat)
{
	uint8_t n;
    DS1302_OUT_GPIO_INIT();
	RST_L;
	Delay1us();
   
	SCLK_L;//�Ƚ�SCLK�õ͵�ƽ��
	Delay1us();
	RST_H; //Ȼ��RST(CE)�øߵ�ƽ��
	Delay1us();

	for (n=0; n<8; n++)//��ʼ���Ͱ�λ��ַ����
	{
        if(addr & 0x01)
        {
            DSIO_H;//���ݴӵ�λ��ʼ����
        }
        else
        {
            DSIO_L;
        }
		addr >>= 1;
		SCLK_H;//������������ʱ��DS1302��ȡ����
		Delay1us();
		SCLK_L;
		Delay1us();
	}
	for (n=0; n<8; n++)//д��8λ����
	{
		if(dat & 0x01)
        {
            DSIO_H;//���ݴӵ�λ��ʼ����
        }
        else
        {
            DSIO_L;
        }
		dat >>= 1;
		SCLK_H;//������������ʱ��DS1302��ȡ����
		Delay1us();
		SCLK_L;
		Delay1us();	
	}	
		 
	RST_L;//�������ݽ���
	Delay1us();
}

/*******************************************************************************
* �� �� ��         : Ds1302Read
* ��������		   : ��ȡһ����ַ������
* ��    ��         : addr
* ��    ��         : dat
*******************************************************************************/

uint8_t Ds1302Read(uint8_t addr)
{
	uint8_t n,dat,dat1;
	RST_L;
	Delay1us();

	SCLK_L;//�Ƚ�SCLK�õ͵�ƽ��
	Delay1us();
	RST_H;//Ȼ��RST(CE)�øߵ�ƽ��
	Delay1us();
    
	for(n=0; n<8; n++)//��ʼ���Ͱ�λ��ַ����
	{
		if(addr & 0x01)
        {
            DSIO_H;//���ݴӵ�λ��ʼ����
        }
        else
        {
            DSIO_L;
        }
		addr >>= 1;
		SCLK_H;//������������ʱ��DS1302��ȡ����
		Delay1us();
		SCLK_L;//DS1302�½���ʱ����������
		Delay1us();
	}
	Delay1us();
    DS1302_IN_GPIO_INIT();
	for(n=0; n<8; n++)//��ȡ8λ����
	{
		dat1 = GET_DSIO;//�����λ��ʼ����
		dat = (dat>>1) | (dat1<<7);
		SCLK_H;
		Delay1us();
		SCLK_L;//DS1302�½���ʱ����������
		Delay1us();
	}
    DS1302_OUT_GPIO_INIT();
	RST_L;
	Delay1us();	//����ΪDS1302��λ���ȶ�ʱ��,����ġ�
	SCLK_H;
	Delay1us();
	DSIO_L;
	Delay1us();
	DSIO_H;
	Delay1us();
	return dat;	
}

/*******************************************************************************
* �� �� ��         : Ds1302Init
* ��������		   : ��ʼ��DS1302.
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/

void Ds1302Init(void)
{
	uint8_t n;
	Ds1302Write(0x8E,0X00);		 //��ֹд���������ǹر�д��������
	for (n=0; n<7; n++)//д��7���ֽڵ�ʱ���źţ�����ʱ��������
	{
		Ds1302Write(WRITE_RTC_ADDR[n],TIME[n]);	
	}
	Ds1302Write(0x8E,0x80);		 //��д��������
}

/*******************************************************************************
* �� �� ��         : Ds1302ReadTime
* ��������		   : ��ȡʱ����Ϣ
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/

void Ds1302ReadTime(void)
{
	uint8_t n;
	for (n=0; n<7; n++)//��ȡ7���ֽڵ�ʱ���źţ�����ʱ��������
	{
		TIME[n] = Ds1302Read(READ_RTC_ADDR[n]);
	}
		
}



































