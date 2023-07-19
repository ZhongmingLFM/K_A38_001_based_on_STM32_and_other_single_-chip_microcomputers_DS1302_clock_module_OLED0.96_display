#ifndef __DS1302_H_
#define __DS1302_H_

#include "reg52.h"
#include "main.h"

//---����ds1302ʹ�õ�IO��---//
sbit DSIO=P1^2;
sbit RST=P1^3;
sbit SCLK=P1^4;

//---����ȫ�ֺ���---//
void Ds1302Write(uint8_t addr, uint8_t dat);
uint8_t Ds1302Read(uint8_t addr);
void Ds1302Init(void);
void Ds1302ReadTime(void);

//---����ȫ�ֱ���--//
extern uint8_t TIME[7];	//����ȫ�ֱ���
#endif