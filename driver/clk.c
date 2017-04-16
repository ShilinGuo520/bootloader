#include "common.h"
#include "rcc.h"
#include "flash.h"
#include "clk.h"

void sys_clk_init(int pll)
{
	unsigned char temp=0;   
 	RCC->CR |= 0x00010000;
	while(!(RCC->CR >> 17));
	RCC->CFGR = 0X00000400; //APB1=DIV2;APB2=DIV1;AHB=DIV1;
	pll -= 2;
	RCC->CFGR |= pll << 18;   
	RCC->CFGR |= 1 << 16;
	FLASH->ACR |= 0x32;	  

	RCC->CR |= 0x01000000;  
	while(!(RCC->CR>>25));
	RCC->CFGR |= 0x00000002;
	while(temp!=0x02)     
	{   
		temp = RCC->CFGR>>2;
		temp &= 0x03;
	}
}

