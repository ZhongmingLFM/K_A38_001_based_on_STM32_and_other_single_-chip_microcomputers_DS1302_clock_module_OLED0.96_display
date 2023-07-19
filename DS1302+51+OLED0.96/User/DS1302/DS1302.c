/************************************************************************************
//�����������������ҡ����Ա�����: https://shop149406681.taobao.com/?spm=a1z10.1-c.0.0.64cb457fKzgKea 
//�Ա����������ؼ��ʣ�K_A38_001
//  �� �� ��   : v1.0
//  ��    ��   : ����������
//  ����Ⱥ :			 1041406448�����������������ע���棩
//    CSDN  ��������������Դ�����б������н���˵����   :��Ƭ��������˹�(�����ؼ��ʣ�K_A38_001)
//    BILIBILI����ʾ��Ƶ�� :����������(�����ؼ��ʣ�K_A38_001)
//  ��������   : 2021-6-21
//  ����޸�   : 2021-11-21
//  ��������   : DS1302����Գ���
//  ��������   : STC89C52RC   ����11.0592
����
DS1302- -------------------------------STC89C52RC
VCC------------------------------------5V
GND------------------------------------GND
CLK------------------------------------P1.4
DAT------------------------------------P1.2
RST------------------------------------P1.3

OLED0.96(IIC) -------------------------STC89C52RC
VCC------------------------------------5V
GND------------------------------------GND
SCL------------------------------------P1^1
SDA------------------------------------P1^0
*************************************************************************************/

#include "DS1302.h"
#include "Delay.h"


//---DS1302д��Ͷ�ȡʱ����ĵ�ַ����---//
//---���ʱ�������� ���λ��дλ;-------//
uint8_t code READ_RTC_ADDR[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d}; 
uint8_t code WRITE_RTC_ADDR[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};

//---DS1302ʱ�ӳ�ʼ��2016��5��7��������12��00��00�롣---//
//---�洢˳�������ʱ��������,�洢��ʽ����BCD��---//
uint8_t TIME[7] = {0x00, 0x39, 0x21, 0x03, 0x04, 0x01, 0x23};

/*******************************************************************************
* �� �� ��         : Ds1302Write
* ��������		   : ��DS1302�����ַ+���ݣ�
* ��    ��         : addr,dat
* ��    ��         : ��
*******************************************************************************/

void Ds1302Write(uint8_t addr, uint8_t dat)
{
	uint8_t n;
	RST = 0;
	SCLK = 0;//�Ƚ�SCLK�õ͵�ƽ��
	RST = 1; //Ȼ��RST(CE)�øߵ�ƽ��

	for (n=0; n<8; n++)//��ʼ���Ͱ�λ��ַ����
	{
		DSIO = addr & 0x01;//���ݴӵ�λ��ʼ����
		addr >>= 1;
		SCLK = 1;//������������ʱ��DS1302��ȡ����
		 
		SCLK = 0;
		 
	}
	for (n=0; n<8; n++)//д��8λ����
	{
		DSIO = dat & 0x01;
		dat >>= 1;
		SCLK = 1;//������������ʱ��DS1302��ȡ����
		 
		SCLK = 0;
		 	
	}	
		 
	RST = 0;//�������ݽ���
	 
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
	RST = 0;
	SCLK = 0;//�Ƚ�SCLK�õ͵�ƽ��
	RST = 1;//Ȼ��RST(CE)�øߵ�ƽ��
	for(n=0; n<8; n++)//��ʼ���Ͱ�λ��ַ����
	{
		DSIO = addr & 0x01;//���ݴӵ�λ��ʼ����
		addr >>= 1;
		SCLK = 1;//������������ʱ��DS1302��ȡ����
		 
		SCLK = 0;//DS1302�½���ʱ����������
		 
	}
	 
	for(n=0; n<8; n++)//��ȡ8λ����
	{
		dat1 = DSIO;//�����λ��ʼ����
		dat = (dat>>1) | (dat1<<7);
		SCLK = 1;
		 
		SCLK = 0;//DS1302�½���ʱ����������
		 
	}

	RST = 0;
	 	//����ΪDS1302��λ���ȶ�ʱ��,����ġ�
	SCLK = 1;
	 
	DSIO = 0;
	 
	DSIO = 1;
	 
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






























