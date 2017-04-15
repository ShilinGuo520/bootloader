#include "common.h"
#include "leds.h"
#include "lib.h"

unsigned char data[100];

void delay(int time)
{
	while(time--){
		if(time%2)
			time--;
		
	}
}

int num;
unsigned char src[] = "ASDFGHJK";


int main()
{	
	unsigned char dec[10];
	int x,y;

	memcpy(dec, src, 10);
	num = 10;
	led_init(1);

	swap(&x, &y);
	while(num--) {
		delay(100000);
		led_on(1);
		delay(100000);
		led_off(1);
	}
	
	while(1);

	return 0;
}

