/************************************************************************************
//（店名“众明工作室”）淘宝链接: https://shop149406681.taobao.com/?spm=a1z10.1-c.0.0.64cb457fKzgKea 
//淘宝店内搜索关键词：K_A38_001
//  版 本 号   : v1.0
//  作    者   : 众明工作室
//  交流群 :			 1041406448（其它更多资料请关注公告）
//    CSDN  （基本参数，资源更新列表，所有接线说明）   :单片机代码搬运工(搜索关键词：K_A38_001)
//    BILIBILI（演示视频） :众明工作室(搜索关键词：K_A38_001)
//  生成日期   : 2021-6-21
//  最近修改   : 2021-11-21
//  功能描述   : DS1302块测试程序
//  测试条件   : STC89C52RC   晶振11.0592
接线
DS1302 --------------------------------STC89C52RC
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
#include "OLED.h"
#include "Uart.h"
#include "Delay.h"
char num=0;

uint8_t D_Buf[11]={0};  //存储年月日
uint8_t Time_Buf[10]={0}; //存储时分秒

uint8_t week[2]={0};               //星期

uint8_t Dis_Data[10];


/*******************************************************************************
* 函 数 名         : datapros()
* 函数功能		   : 时间读取处理转换函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/

void datapros() 	 
{
   	Ds1302ReadTime();
	D_Buf[0] = '2';				//年
	D_Buf[1] = '0';				 
	D_Buf[2] = TIME[6]/16+0x30;				//年
	D_Buf[3] = TIME[6]%16+0x30;				 
	D_Buf[4] = ':';
	D_Buf[5] = TIME[4]/16+0x30;				//月
	D_Buf[6] = TIME[4]%16+0x30;	
	D_Buf[7] = ':';
	D_Buf[8] = TIME[3]/16+0x30;				//日
	D_Buf[9] = TIME[3]%16+0x30;
	
	D_Buf[10] = '\0';
	
	Time_Buf[0] = TIME[2]/16+0x30;				//时
	Time_Buf[1] = TIME[2]%16+0x30;				 
	Time_Buf[2] = ':';
	Time_Buf[3] = TIME[1]/16+0x30;				//分
	Time_Buf[4] = TIME[1]%16+0x30;	
	Time_Buf[5] = ':';
	Time_Buf[6] = TIME[0]/16+0x30;				//秒
	Time_Buf[7] = TIME[0]%16+0x30;
	
	Time_Buf[8] = '\0';
	
//	week[0] = TIME[5]+0x30;				//星期
	week[0] = TIME[5];				//星期
	week[1] = '\0';

}


/*******************************************************************************
* 函数名         :DigDisplay()
* 函数功能		 :数码管显示函数
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/
void DigDisplay()
{
	
	OLED_P8x16Str(20,0,D_Buf);
	OLED_P16x16Ch(40,2,7);
	OLED_P16x16Ch(56,2,8);
	OLED_P16x16Ch(72,2,week[0]);
	OLED_P8x16Str(30,4,Time_Buf);

	
}


void main()//主函数模块// 
{ 

	OLED_Init(); //OLED初始化
	UartInit();
	//Ds1302Init();
	while(1) 
	{ 

		datapros();	 //数据处理函数
		DigDisplay();//数码管显示函数		
		
		
		

	} 
} 


