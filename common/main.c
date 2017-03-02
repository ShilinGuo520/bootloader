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
	int a;
	led_init(1);
	a = 20;
	a = a + 100;
	while(a) {
		a--;
		delay(a);
		led_on(1);
	}

	return 0;
}

