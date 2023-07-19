#ifndef __TIME_H
#define	__TIME_H

#include "reg52.h"
#include "main.h"

extern uint8_t Duty;	   //初始为15角度90
extern uint8_t Period;	//周期20ms
extern uint8_t times;		//计数
void time0init(void);

#endif

