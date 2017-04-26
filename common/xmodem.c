/**********************************************
file name:xmodem
date:2017-04-18
***********************************************/

#include "glib.h"
#include "uart.h"
#include "timer.h"

#define SOH	0x01
#define EOT	0x04
#define	ACK	0x06
#define NAK	0x15
#define CAN	0x18

#define NAK_CONT	5
unsigned char xmodem_buff[132];
int xmodem_cont;

void xmodem(void)
{
	unsigned char buff[10];
	int buff_cont = 0;
	int try = NAK_CONT;
	
	xmodem_cont = 0;	

	printf("\n\rWait Received Data\n\r");
	while(try--) {
		printf("Wait %d s\r", try * 3);
		fputc(NAK);
		set_time_out(3000);
		while(get_time_out()) {
			memset(buff, 0, 10);
			buff_cont = uart_get_buff(buff);
			if (buff_cont) {
				memcpy(&(xmodem_buff[xmodem_cont]), buff, buff_cont);
				xmodem_cont += buff_cont;
				if (xmodem_buff[0] == SOH)
					goto Rec_data;
				else {
					xmodem_cont = 0;
					buff_cont = 0;
					memset(buff, 0, 10);
					memset(xmodem_buff, 0, 132);
					continue;
				}
			}
		}
	}
	printf("\n\rNot received SOH,Try cont out \n\r");
	return ;

Rec_data:
	while(1) {
		set_time_out(1000);
		while((xmodem_cont < 132 ) && get_time_out()) {
			xmodem_cont += uart_get_buff(&(xmodem_buff[xmodem_cont]));
		}
		fputc(ACK);
		xmodem_cont = 0;
		//TODO: Copy data to flash
		memset(xmodem_buff, 0, 132);
		while((xmodem_cont == 0) && get_time_out())
			xmodem_cont += uart_get_buff(&(xmodem_buff[xmodem_cont]));
		
		if(xmodem_buff[0] == EOT)
			break;
		if(get_time_out() <= 0) {
			printf("\n\rReceived Time Out\n\r");
			return ;
		}
	}
	//TODO: End transport
	fputc(ACK);
	xmodem_cont = 0;

	while(xmodem_cont)
		xmodem_cont += uart_get_buff(&(xmodem_buff[xmodem_cont]));
	
	fputc(ACK);

	printf("\n\rReceived Done\n\r");
}


