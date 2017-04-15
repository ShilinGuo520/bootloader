/*********************************
 * leds driver
 *********************************/

#include "leds.h"
#include "config.h"

void led_init(char num)
{
	RCC->APB2ENR |= 1 << 3;

	if (LED_PIN > 7) {
		GPIOB->CRH &= (~(0xF << ((LED_PIN - 8) * 4)));
		GPIOB->CRH |= (0x1 << ((LED_PIN - 8) * 4));
	} else {
		GPIOB->CRL &= (~(0xF << (((LED_PIN) % 7) * 4)));
		GPIOB->CRL |= (0x1 << (((LED_PIN) % 7) * 4));
	}
}

void led_on(char num)
{
	GPIOB->ODR |= (1 << LED_PIN);
}

void led_off(char num)
{
	GPIOB->ODR &= ~(1 << LED_PIN);
}

void leds_blink(char num)
{
	led_off(num);
	led_on(num);
}
