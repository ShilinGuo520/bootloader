#include "common.h"
#include "leds.h"

unsigned char data[100];

void delay(int time)
{
	while(time--){
		if(time%2)
			time--;
		
	}
}

int main()
{
	led_init(1);
	while(1) {
		delay(100000);
		led_on(1);
		delay(100000);
		led_off(1);
	}

	return 0;
}

