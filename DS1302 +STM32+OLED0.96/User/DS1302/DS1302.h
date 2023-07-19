#ifndef __DS1302_H
#define __DS1302_H
										  	  
#include "stm32f10x.h"

#define DSIO_H   GPIO_SetBits(GPIOA,GPIO_Pin_0)
#define DSIO_L   GPIO_ResetBits(GPIOA,GPIO_Pin_0)
#define RST_H    GPIO_SetBits(GPIOA,GPIO_Pin_1)
#define RST_L    GPIO_ResetBits(GPIOA,GPIO_Pin_1)
#define SCLK_H   GPIO_SetBits(GPIOA,GPIO_Pin_2)
#define SCLK_L   GPIO_ResetBits(GPIOA,GPIO_Pin_2)
#define GET_DSIO  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)
////---定义ds1302使用的IO口---//
//sbit DSIO=P1^0;
//sbit RST=P1^1;
//sbit SCLK=P1^2;

//---定义全局函数---//
void Ds1302Write(uint8_t addr, uint8_t dat);
uint8_t Ds1302Read(uint8_t addr);
void Ds1302Init(void);
void Ds1302ReadTime(void);

//---加入全局变量--//
extern uint8_t TIME[7];	//加入全局变量

#endif






































