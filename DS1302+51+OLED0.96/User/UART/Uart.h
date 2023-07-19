#ifndef __UART_H
#define	__UART_H

#include <reg52.h>
#include "main.h"

void UartInit(void);
void UartSend(uint8_t dat);
void UartSendStr(uint8_t *p);

extern uint8_t R_DatBuf[10];
extern uint8_t T_DatBuf[10];
#endif
