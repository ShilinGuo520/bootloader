/*********************************
 * leds driver
 *********************************/

#include "leds.h"

void led_init(char num)
{
	RCC->APB2ENR |= 1 << 2;
	GPIOA->CRL &= 0xFFFFFFF0;
	GPIOA->CRL |= 0x00000003; 
}

void led_on(char num)
{
	GPIOA->ODR |= 0xFFFFFFFF;
}

void led_off(char num)
{
	GPIOA->ODR &= 0x00000001;
}

void leds_blink(char num)
{
	led_off(num);
	led_on(num);
}
