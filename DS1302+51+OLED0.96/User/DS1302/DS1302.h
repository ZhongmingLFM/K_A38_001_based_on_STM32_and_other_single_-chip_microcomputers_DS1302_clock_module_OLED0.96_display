#ifndef __DS1302_H_
#define __DS1302_H_

#include "reg52.h"
#include "main.h"

//---定义ds1302使用的IO口---//
sbit DSIO=P1^2;
sbit RST=P1^3;
sbit SCLK=P1^4;

//---定义全局函数---//
void Ds1302Write(uint8_t addr, uint8_t dat);
uint8_t Ds1302Read(uint8_t addr);
void Ds1302Init(void);
void Ds1302ReadTime(void);

//---加入全局变量--//
extern uint8_t TIME[7];	//加入全局变量
#endif