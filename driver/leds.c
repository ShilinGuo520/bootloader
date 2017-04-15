/*********************************
 * leds driver
 *********************************/

#include "leds.h"

void led_init(char num)
{
	RCC->APB2ENR |= 1 << 3;
	GPIOB->CRL &= 0x00000000;
	GPIOB->CRL |= 0x33333333; 
	GPIOB->CRH &= 0x00000000;
	GPIOB->CRH |= 0x33333333;
}

void led_on(char num)
{
	GPIOB->ODR |= 0xFFFFFFFF;
}

void led_off(char num)
{
	GPIOB->ODR &= 0x00000000;
}

void leds_blink(char num)
{
	led_off(num);
	led_on(num);
}
