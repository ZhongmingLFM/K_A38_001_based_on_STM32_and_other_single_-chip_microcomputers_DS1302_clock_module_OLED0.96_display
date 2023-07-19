#ifndef __OLED_H_
#define __OLED_H_

#include "reg52.h"
#include "main.h"
sbit SCL=P1^1; //串行时钟
sbit SDA=P1^0; //串行数据

#define high 1
#define low 0

#define	Brightness	0xCF 
#define X_WIDTH 	128
#define Y_WIDTH 	64


void OLED_Set_Pos(uint8_t x, uint8_t y);
void OLED_Fill(uint8_t bmp_dat);
void OLED_CLS(void);
void OLED_Init(void);
void OLED_P6x8Str(uint8_t x,uint8_t y,uint8_t ch[]);
void OLED_P8x16Str(uint8_t x,uint8_t y,uint8_t ch[]);
void OLED_P16x16Ch(uint8_t x,uint8_t y,uint8_t N);
void OLED_ShowCN(uint8_t x, uint8_t y, uint8_t N);
void Draw_BMP(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1,uint8_t BMP[]);
#endif