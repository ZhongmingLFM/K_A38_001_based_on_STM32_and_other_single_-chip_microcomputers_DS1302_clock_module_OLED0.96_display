#include "main.h"
#include "Delay.h"
#include "intrins.h"
////��ʱnms  1T��Ƭ����
////ע��nms�ķ�Χ
//void Delayus(uint16_t Nus)		//@11.0592MHz
//{
//	uint16_t k;
//	for(k=0;k<Nus;k++)
//	{
//		_nop_();
//		_nop_();
//		_nop_();
//	}

//}

void DelayMs(uint16_t Nms)
{
	uint16_t k;
	uint8_t i, j;
	for(k=0;k<Nms;k++)
	{
			_nop_();
			i = 2;
			j = 190;
			do
			{
				while (--j);
			} while (--i);
	}
}
//��ʱ��

void DelayS(uint16_t Ns)
{
	uint16_t i;
	for(i=0;i<Ns;i++)
	{
		DelayMs(1000);
	}
}
