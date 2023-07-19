/************************************************************************************
//（店名“众明工作室”）淘宝链接: https://shop149406681.taobao.com/?spm=a1z10.1-c.0.0.64cb457fKzgKea 
//淘宝店内搜索关键词：K_A37_005
//  版 本 号   : v1.0
//  作    者   : 众明工作室
//  交流群 :			 1041406448（其它更多资料请关注公告）
//    CSDN  （基本参数，资源更新列表，所有接线说明）   :单片机代码搬运工(搜索关键词：K_A37_005)
//    BILIBILI（演示视频） :众明工作室(搜索关键词：K_A37_005)
//  生成日期   : 2021-6-21
//  最近修改   : 2021-11-21
//  功能描述   : ADS1115块测试程序
//  测试条件   : STM32F103C8T6   晶振8M  系统时钟72M
接线
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

//---DS1302写入和读取时分秒的地址命令---//
//---秒分时日月周年 最低位读写位;-------//
uint8_t  READ_RTC_ADDR[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d}; 
uint8_t  WRITE_RTC_ADDR[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};

//---DS1302时钟初始化2013年1月1日星期二12点00分00秒。---//
//---存储顺序是秒分时日月周年,存储格式是用BCD码---//
uint8_t TIME[7] = {0x00, 0x47, 0x21, 0x29, 0x3, 0x03, 0x23};

/*******************************************************************************
配置成推挽输出模式
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
数据引脚配置成上拉输入模式
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
   
	SCLK_L;//先将SCLK置低电平。
	Delay1us();
	RST_H; //然后将RST(CE)置高电平。
	Delay1us();

	for (n=0; n<8; n++)//开始传送八位地址命令
	{
        if(addr & 0x01)
        {
            DSIO_H;//数据从低位开始传送
        }
        else
        {
            DSIO_L;
        }
		addr >>= 1;
		SCLK_H;//数据在上升沿时，DS1302读取数据
		Delay1us();
		SCLK_L;
		Delay1us();
	}
	for (n=0; n<8; n++)//写入8位数据
	{
		if(dat & 0x01)
        {
            DSIO_H;//数据从低位开始传送
        }
        else
        {
            DSIO_L;
        }
		dat >>= 1;
		SCLK_H;//数据在上升沿时，DS1302读取数据
		Delay1us();
		SCLK_L;
		Delay1us();	
	}	
		 
	RST_L;//传送数据结束
	Delay1us();
}

/*******************************************************************************
* 函 数 名         : Ds1302Read
* 函数功能		   : 读取一个地址的数据
* 输    入         : addr
* 输    出         : dat
*******************************************************************************/

uint8_t Ds1302Read(uint8_t addr)
{
	uint8_t n,dat,dat1;
	RST_L;
	Delay1us();

	SCLK_L;//先将SCLK置低电平。
	Delay1us();
	RST_H;//然后将RST(CE)置高电平。
	Delay1us();
    
	for(n=0; n<8; n++)//开始传送八位地址命令
	{
		if(addr & 0x01)
        {
            DSIO_H;//数据从低位开始传送
        }
        else
        {
            DSIO_L;
        }
		addr >>= 1;
		SCLK_H;//数据在上升沿时，DS1302读取数据
		Delay1us();
		SCLK_L;//DS1302下降沿时，放置数据
		Delay1us();
	}
	Delay1us();
    DS1302_IN_GPIO_INIT();
	for(n=0; n<8; n++)//读取8位数据
	{
		dat1 = GET_DSIO;//从最低位开始接收
		dat = (dat>>1) | (dat1<<7);
		SCLK_H;
		Delay1us();
		SCLK_L;//DS1302下降沿时，放置数据
		Delay1us();
	}
    DS1302_OUT_GPIO_INIT();
	RST_L;
	Delay1us();	//以下为DS1302复位的稳定时间,必须的。
	SCLK_H;
	Delay1us();
	DSIO_L;
	Delay1us();
	DSIO_H;
	Delay1us();
	return dat;	
}

/*******************************************************************************
* 函 数 名         : Ds1302Init
* 函数功能		   : 初始化DS1302.
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/

void Ds1302Init(void)
{
	uint8_t n;
	Ds1302Write(0x8E,0X00);		 //禁止写保护，就是关闭写保护功能
	for (n=0; n<7; n++)//写入7个字节的时钟信号：分秒时日月周年
	{
		Ds1302Write(WRITE_RTC_ADDR[n],TIME[n]);	
	}
	Ds1302Write(0x8E,0x80);		 //打开写保护功能
}

/*******************************************************************************
* 函 数 名         : Ds1302ReadTime
* 函数功能		   : 读取时钟信息
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/

void Ds1302ReadTime(void)
{
	uint8_t n;
	for (n=0; n<7; n++)//读取7个字节的时钟信号：分秒时日月周年
	{
		TIME[n] = Ds1302Read(READ_RTC_ADDR[n]);
	}
		
}



































