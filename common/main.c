#include "common.h"
#include "leds.h"
#include "uart.h"
#include "glib.h"

unsigned char data[100];

void delay(int time)
{
	while(time--){
		if(time%2)
			time--;
		
	}
}

int num;

int main()
{	
	unsigned char dec[10];
	int x,y;
	unsigned char buff[100];
	num = 10;
	uart_init(8, 115200);
	led_init(1);

	printf("Build Info:\n\rTime:%s\n\rDate:%s\n\r", __TIME__, __DATE__);

	while(num--) {
		delay(100000);
		led_on(1);
		delay(100000);
		led_off(1);
	}
	
	while(1);

	return 0;
}

