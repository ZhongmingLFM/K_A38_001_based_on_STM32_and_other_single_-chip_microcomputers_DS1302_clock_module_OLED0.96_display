# K_A38_001_based_on_STM32_and_other_single_-chip_microcomputers_DS1302_clock_module_OLED0.96_display
K_A38_001_based_on_STM32_and_other_single_-chip_microcomputers_DS1302_clock_module_OLED0.96_display
这里有中英文说明 前部分为中文说明 后半部分为英文说明 请悉知

Here are Chinese and English description The previous part of the Chinese description is the English description in English, please know how to know

注：文档手册在工程文件的DOC文件夹内

Note: The document manual is in the DOC folder of the engineering file

如果发现程序有BUG 或者有可以改进的地方 欢迎联系我们

If you find that the program has bugs or can be improved, please contact us

- [所有资源导航](#所有资源导航)
- [资源说明](#资源说明)
- [基本参数](#基本参数)
  * [参数](#参数)
  * [引脚说明](#引脚说明)
- [驱动说明](#驱动说明)
  * [时序](#时序)
  * [对应程序](#对应程序)
- [部分代码说明](#部分代码说明)
  * [接线引脚定义](#接线引脚定义)
    + [STC89C52RC+DS1302时钟模块](#stc89c52rc-ds1302时钟模块)
    + [STM32F103C8T6+DS1302时钟模块](#stm32f103c8t6-ds1302时钟模块)
- [基础知识学习与相关资料下载](#基础知识学习与相关资料下载)
- [视频效果展示与程序资料获取](#视频效果展示与程序资料获取)
- [注意事项](#注意事项)
- [接线说明](#接线说明)
  * [STC89C52RC](#stc89c52rc)
  * [STM32F103C8T6](#stm32f103c8t6)
- [All resource navigation](#all-resource-navigation)
- [Resource description](#resource-description)
- [basic parameters](#basic-parameters)
  * [parameter](#parameter)
  * [pin explanation](#pin-explanation)
- [Drive Instructions](#drive-instructions)
  * [timing](#timing)
  * [corresponding program](#corresponding-program)
- [Partial code description](#partial-code-description)
  * [Wiring pin definition](#wiring-pin-definition)
    + [STC89C52RC+DS1302 clock module](#stc89c52rc-ds1302-clock-module)
    + [STM32F103C8T6+DS1302 clock module](#stm32f103c8t6-ds1302-clock-module)
- [Basic knowledge learning and related information download](#basic-knowledge-learning-and-related-information-download)
- [Video effect display and program data acquisition](#video-effect-display-and-program-data-acquisition)
- [Notice](#notice)
- [Wiring description](#wiring-description)
  * [STC89C52RC](#stc89c52rc-1)
  * [STM32F103C8T6](#stm32f103c8t6-1)

@[TOC](K_A38_001 基于STM32等单片机驱动DS1302时钟模块  OLED0.96显示)

@[TOC](K_A38_001 based on STM32 and other single -chip microcomputers DS1302 clock module OLED0.96 display)

K_A38_001_based_on_STM32_and_other_single_-chip_microcomputers_DS1302_clock_module_OLED0.96_display

![请添加图片描述](https://img-blog.csdnimg.cn/2c71b8b13c2044f8a81a9a9e0b6e2717.jpeg#pic_center)


#  所有资源导航
[**其他资料目录**](https://blog.csdn.net/lfmnlxx79691557/article/details/128323460?spm=1001.2014.3001.5501)     	直戳跳转
# 资源说明

| 单片机型号 | 测试条件|模块名称 |代码功能 |
|:--------:| -------------:| -------------:|-------------:|
| STC89C52RC | 晶振11.0592M	 |DS1302时钟模块|STC89C52RC驱动DS1302时钟模块  串口与OLED0.96双显示 |
| STM32F103C8T6 | 晶振8M/系统时钟72M |DS1302时钟模块 |STM32F103C8T6驱动DS1302时钟模块 串口与OLED0.96双显示 |


# 基本参数
## 参数

实时时钟具有能计算 2100 年之前的秒 分 时 日 日期 星期 月 年的能力 还有闰年调整的能力 
31 X8 位暂存数据存储 RAM 
串行 I/O 口方式使得管脚数量最少 
宽范围工作电压 2.0 5.5V 
工作电流 2.0V 时,小于 300nA 
读/写时钟或 RAM 数据时 有两种传送方式 单字节传送和多字节传送 字符组方式 
8 脚 DIP 封装或可选的 8 脚 SOIC 封装 根据表面装配 
简单 3 线接口 
与 TTL 兼容 Vcc=5V 
可选工业级温度范围 -40 +85 °C


## 引脚说明

DS1302时钟模块 | 	引脚说明
-------- | -----
VIN	 | 正极 5V供电
GND | 	GND 电源负极
RST	 | 复位脚 
DAT	 | 数据输入/输出引脚
CLK	 | 串行时钟


# 驱动说明

## 时序

![请添加图片描述](https://img-blog.csdnimg.cn/9bbe0be68c944e6ca558bc4e996a5097.png)


## 对应程序
以51为例
```javascript
/*******************************************************************************
* 函 数 名         : Ds1302Write
* 函数功能		   : 向DS1302命令（地址+数据）
* 输    入         : addr,dat
* 输    出         : 无
*******************************************************************************/

void Ds1302Write(uint8_t addr, uint8_t dat)
{
	uint8_t n;
	RST = 0;
	SCLK = 0;//先将SCLK置低电平。
	RST = 1; //然后将RST(CE)置高电平。
	for (n=0; n<8; n++)//开始传送八位地址命令
	{
		DSIO = addr & 0x01;//数据从低位开始传送
		addr >>= 1;
		SCLK = 1;//数据在上升沿时，DS1302读取数据		 
		SCLK = 0;		 
	}
	for (n=0; n<8; n++)//写入8位数据
	{
		DSIO = dat & 0x01;
		dat >>= 1;
		SCLK = 1;//数据在上升沿时，DS1302读取数据		 
		SCLK = 0;		 	
	}			 
	RST = 0;//传送数据结束	 
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
	RST = 0;
	SCLK = 0;//先将SCLK置低电平。
	RST = 1;//然后将RST(CE)置高电平。
	for(n=0; n<8; n++)//开始传送八位地址命令
	{
		DSIO = addr & 0x01;//数据从低位开始传送
		addr >>= 1;
		SCLK = 1;//数据在上升沿时，DS1302读取数据		 
		SCLK = 0;//DS1302下降沿时，放置数据		 
	}	 
	for(n=0; n<8; n++)//读取8位数据
	{
		dat1 = DSIO;//从最低位开始接收
		dat = (dat>>1) | (dat1<<7);
		SCLK = 1;		 
		SCLK = 0;//DS1302下降沿时，放置数据		 
	}
	RST = 0;
	 	//以下为DS1302复位的稳定时间,必须的。
	SCLK = 1;
	DSIO = 0;	 
	DSIO = 1;	 
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
```

# 部分代码说明
## 接线引脚定义

需要自定义引脚可在此处更改，STM32要自定义引脚的话也要注意引脚时钟使能的更改

### STC89C52RC+DS1302时钟模块
```javascript
//DS1302时钟模块引脚定义
sbit DSIO=P1^2;
sbit RST=P1^3;
sbit SCLK=P1^4;


//OLED0.96模块引脚定义
sbit SCL=P1^1; //串行时钟
sbit SDA=P1^0; //串行数据
```

### STM32F103C8T6+DS1302时钟模块
```javascript
//DS1302时钟模块引脚定义
#define DSIO_H   GPIO_SetBits(GPIOA,GPIO_Pin_0)
#define DSIO_L   GPIO_ResetBits(GPIOA,GPIO_Pin_0)
#define RST_H    GPIO_SetBits(GPIOA,GPIO_Pin_1)
#define RST_L    GPIO_ResetBits(GPIOA,GPIO_Pin_1)
#define SCLK_H   GPIO_SetBits(GPIOA,GPIO_Pin_2)
#define SCLK_L   GPIO_ResetBits(GPIOA,GPIO_Pin_2)

//OLED0.96模块引脚定义					
#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_8)//SCL
#define OLED_SCLK_Set() GPIO_SetBits(GPIOB,GPIO_Pin_8)

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_9)//SDA
#define OLED_SDIN_Set() GPIO_SetBits(GPIOB,GPIO_Pin_9)
```


# 基础知识学习与相关资料下载

1、[STC89C52RC程序下载](https://blog.csdn.net/lfmnlxx79691557/article/details/127114912?spm=1001.2014.3001.5501)			直戳跳转

2、STM32F103C8T6程序下载		

(1)[串口下载](https://blog.csdn.net/lfmnlxx79691557/article/details/122862183?spm=1001.2014.3001.5501)                直戳跳转 

(2)[ST-LINK下载](https://blog.csdn.net/lfmnlxx79691557/article/details/127140554?spm=1001.2014.3001.5501)             直戳跳转

(3)[J-LINK下载](https://blog.csdn.net/lfmnlxx79691557/article/details/127140823?spm=1001.2014.3001.5501)              直戳跳转

(4)[DAP-LINK下载](https://blog.csdn.net/lfmnlxx79691557/article/details/127141244?spm=1001.2014.3001.5501)            直戳跳转


3、[OLED0.96程序说明](https://blog.csdn.net/lfmnlxx79691557/article/details/127208887?spm=1001.2014.3001.5501)			直戳跳转


4、串口助手下载与使用

(1)[安信可调试助手使用](https://blog.csdn.net/lfmnlxx79691557/article/details/128335660?spm=1001.2014.3001.5502) 						直戳跳转

(2) [sscom33串口调试助手使用](https://blog.csdn.net/lfmnlxx79691557/article/details/128335808?spm=1001.2014.3001.5502)			直戳跳转

(3)[STC-ISP串口调试助手使用](https://blog.csdn.net/lfmnlxx79691557/article/details/128335896?spm=1001.2014.3001.5502)			    直戳跳转


# 视频效果展示与程序资料获取

[视频连接](https://www.bilibili.com/video/BV1Zm4y1C7cF/?vd_source=7933b82b52c9cbf1c7966eb9f0dbd29f)  	直戳跳转

资料获取 （可直接下载仓库）

# 注意事项

1、VCC GND请勿接反，接反易烧

2、OLED显示异常时，排除接线接触不良

# 接线说明

## STC89C52RC   
```javascript

/************************************************************************************
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
```
## STM32F103C8T6 
```javascript
  
/************************************************************************************
//  功能描述   : DS1302块测试程序
//  测试条件   : STM32F103C8T6   晶振8M  系统时钟72M
接线
DS1302---------------------------------STM32F103C8T6
VCC------------------------------------5V
GND------------------------------------GND
CLK------------------------------------PA_2 //
DAT------------------------------------PA_0 //	
RST------------------------------------PA_1 //	

OLED0.96
VCC------------------------------------3.3V
GND------------------------------------GND
SCL------------------------------------PB_8 //SCL
SDA------------------------------------PB_9 //SDA	
*************************************************************************************/
```

![Please add picture description](https://img-blog.csdnimg.cn/2c71b8b13c2044f8a81a9a9e0b6e2717.jpeg#pic_center)


# All resource navigation
[ Other data catalog ](https://blog.csdn.net/lfmnlxx79691557/article/details/128323460?spm=1001.2014.3001.5501)  Direct link to jump
#  Resource description
| Single -chip Machine Model | Test Conditions | Module Name | Code Function |
|:--------:| -------------:| -------------:|-------------:|
| STC89C52RC | Crystal Episode 11.0592M | DS1302 Clock Module | STC89C52RC Drive DS1302 Clock Module serial port and OLED0.96 dual display |
| STM32F103C8T6 | Crystal 8M/System Clock 72M | DS1302 Clock Module | STM32F103C8T6 Drive DS1302 clock module serial port and OLED0.96 dual display |


# basic parameters
## parameter
The real -time clock has the ability to calculate the time of the daily date of the second daily date of 2100 years before 2100 years, and the ability to adjust the leap year
31 X8 -bit temporarily stored data storage RAM
Serial I/O port method makes the number of pipes the least
Wide -range working voltage 2.0 5.5V
When the working current is 2.0V, it is less than 300NA
When reading/write clocks or RAM data
8 -pin DIP packaging or optional 8 -pin SOIC package is assembled according to the surface
Simple 3 line interface
Compatible with TTL compatible VCC = 5V
Optional industrial -grade temperature range -40 +85 ° C


## pin explanation

DS1302 clock module | pin explanation
-------- | -------
Vin | Power 5V power supply
GND | GND power supply negative electrode
Rst | reset foot
DAT | Data input/output pin
CLK | Serial clock


# Drive Instructions

## timing

![Please add picture description](https://img-blog.csdnimg.cn/9bbe0be68c944e6ca558bc4e996a5097.png)

## corresponding program
Take 51 as an example
```javascript
/*************************************************** *************************************
* Sweeping name: DS1302write
* Function function: to DS1302 command (address+data)
* Input: addr, Dat
* Output: None
************************************************* *******************************************/

void Ds1302Write(uint8_t addr, uint8_t dat)
{
	uint8_t n;
	RST = 0;
	SCLK = 0; // SCLK is lowered first.
	RST = 1; // Then put the RST (CE) high level.
	// Start transmitting the eight -bit address command
	for (n=0; n<8; n++)
	{
		DSIO = addr & 0x01; // The data is transmitted from the low position
		addr >>= 1;
		SCLK = 1; // When the data is rising edge, DS1302 reads the data
		SCLK = 0;
	}
	for (n=0; n<8; n++)// Write 8 -bit data
	{
		DSIO = dat & 0x01;
		dat >>= 1;
		SCLK = 1; // When the data is rising edge, DS1302 reads the data
		SCLK = 0;		 	
	}			 
	RST = 0; // Transmit data End
}

/*************************************************** *************************************
* Function name: DS1302read
* Function function: Read the data of an address
* Input: ADDR
* Output: DAT
************************************************* *******************************************/

uint8_t Ds1302Read(uint8_t addr)
{
	uint8_t n,dat,dat1;
	RST = 0;
	SCLK = 0;// SCLK is lowered first.
	RST = 1; // Then put the RST (CE) high level.
	for(n=0; n<8; n++) // Start transmitting the eight -bit address command
	{
		DSIO = addr & 0x01;// The data is transmitted from the low position
		addr >>= 1;
		SCLK = 1; // When the data is rising edge, DS1302 reads the data
		SCLK = 0;// DS1302 When the edge of the drop, put the data
	}
	for(n=0; n<8; n++) // Read 8 -bit data
	{
		dat1 = DSIO;// Start from the lowest position to receive
		dat = (dat>>1) | (dat1<<7);
		SCLK = 1;		 
		SCLK = 0;// DS1302 When the edge of the drop, put the data
	}
	RST = 0;
	// The following is the stable time of DS1302 reset, necessary.
	SCLK = 1;
	DSIO = 0;	 
	DSIO = 1;	 
	return dat;	
}

/*************************************************** *************************************
* Function name: DS1302init
* Function function: initialize DS1302.
* Input: None
* Output: None
************************************************* *******************************************/

void Ds1302Init(void)
{
	uint8_t n;
	Ds1302Write(0x8E,0X00);	 // Forbidden to write protection, that is, to close the writing protection function
	for (n=0; n<7; n++) // Write a 7 -byte clock signal: the anniversary of the month and the moon in the second second
	{
		Ds1302Write(WRITE_RTC_ADDR[n],TIME[n]);	
	}
	Ds1302Write(0x8E,0x80);	 // Open the writing protection function
}

/*************************************************** *************************************
* Sweet name: DS1302readtime
* Function function: Read clock information
* Input: None
* Output: None
************************************************* *******************************************/

void Ds1302ReadTime(void)
{
	uint8_t n;
	// Read the 7 -byte clock signal: the anniversary of the month and the month of the second time
	for (n=0; n<7; n++)	
	{
		TIME[n] = Ds1302Read(READ_RTC_ADDR[n]);
	}
}

```

# Partial code description
## Wiring pin definition
You need to customize the pin can be changed here. If STM32 needs to customize the pin, you should also pay attention
### STC89C52RC+DS1302 clock module
```javascript
// DS1302 clock module pins definition
sbit DSIO=P1^2;
sbit RST=P1^3;
sbit SCLK=P1^4;

//OLED0.96 module pin definition
sbit SCL=P1^1; // Serial clock
sbit SDA=P1^0;// Serial data
```
### STM32F103C8T6+DS1302 clock module
```javascript
// DS1302 clock module pins definition
#define DSIO_H   GPIO_SetBits(GPIOA,GPIO_Pin_0)
#define DSIO_L   GPIO_ResetBits(GPIOA,GPIO_Pin_0)
#define RST_H    GPIO_SetBits(GPIOA,GPIO_Pin_1)
#define RST_L    GPIO_ResetBits(GPIOA,GPIO_Pin_1)
#define SCLK_H   GPIO_SetBits(GPIOA,GPIO_Pin_2)
#define SCLK_L   GPIO_ResetBits(GPIOA,GPIO_Pin_2)

//OLED0.96 module pin definition
#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_8)//SCL
#define OLED_SCLK_Set() GPIO_SetBits(GPIOB,GPIO_Pin_8)

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_9)//SDA
#define OLED_SDIN_Set() GPIO_SetBits(GPIOB,GPIO_Pin_9)
```


# Basic knowledge learning and related information download

1. [STC89C52RC program download](https://blog.csdn.net/lfmnlxx79691557/article/details/127114912?spm=1001.2014.3001.5501)   Direct link to jump

2. STM32F103C8T6 program download

(1) [serial port download](https://blog.csdn.net/lfmnlxx79691557/article/details/122862183?spm=1001.2014.3001.5501)   Direct link to jump

(2) [ST-LINK Download](https://blog.csdn.net/lfmnlxx79691557/article/details/127140554?1001.2014.3001.5501)   Direct link to jump

(3) [j-link download](https://blog.csdn.net/lfmnlxx79691557/article/details/127140823?1001.2014.3001.5501)   Direct link to jump

(4) [dap-link download](https://blog.csdn.net/lfmnlxx79691557/article/details/127141244?spm=1001.2014.3001.5501)  Direct link to jump

3. [OLED0.96 Program Instructions](https://blog.csdn.net/lfmnlxx79691557/article/details/127208887?spm=1001.2014.3001.5501)   Direct link to jump

4. Download and use serial assistant

	(1) [Anxin's debugging assistant use](https://blog.csdn.net/lfmnlxx79691557/article/details/128335660?spm=1001.2014.3001.5502)   Direct link to jump

	(2) [SSCOM33 serial debug assistant use](https://blog.csdn.net/lfmnlxx79691557/article/details/128335808?spm=1001.2014.3001.5502)   Direct link to jump

	(3) [STC -ISP serial debugging assistant use](https://blog.csdn.net/lfmnlxx79691557/article/details/128335896?spm=1001.2014.3001.5502)   Direct link to jump

# Video effect display and program data acquisition

[Video Connection](https://www.bilibili.com/video/BV1Zm4y1C7cF/?vd_source=7933b82b52c9cbf1c7966eb9f0dbd29f) Stranding jumping

Data acquisition  (can download the warehouse directly)


# Notice

1. Please do not recalculate VCC GND.

2. When the OLED display is abnormal, exclude poor wiring contact

#  Wiring description

## STC89C52RC
```javascript
/********************************************************************************************
// Function description: DS1302 test program
// Test conditions: STC89C52RC Crystal Epicer 11.0592
wiring
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

*************************************************************************************************
```
## STM32F103C8T6
```javascript
  
/********************************************************************************************
// Function description: DS1302 test program
// Test conditions: STM32F103C8T6 Crystal 8M System Clock 72M
wiring
DS1302---------------------------------STM32F103C8T6
VCC------------------------------------5V
GND------------------------------------GND
CLK------------------------------------PA_2 //
DAT------------------------------------PA_0 //	
RST------------------------------------PA_1 //	

OLED0.96
VCC------------------------------------3.3V
GND------------------------------------GND
SCL------------------------------------PB_8 //SCL
SDA------------------------------------PB_9 //SDA


*************************************************************************************************
```
