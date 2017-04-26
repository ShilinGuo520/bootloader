/**********************************************
file name:xmodem
date:2017-04-18
***********************************************/

#include "glib.h"
#include "uart.h"
#include "timer.h"
#include "flash.h"

#define SOH	0x01
#define EOT	0x04
#define	ACK	0x06
#define NAK	0x15
#define CAN	0x18

#define NAK_CONT	10
unsigned char xmodem_buff[132];
int xmodem_cont;

int xmodem_data_check(unsigned char num, unsigned char *buff)
{
	/*check num*/
	int i = 0;
	if ((buff[0] != SOH) || (buff[1] != num) || (buff[2] != (255 - num)))
		return -1;

	return 0;	
}

void xmodem_write_flash(u32 addr,u8 *buf)
{
    int i = 0;
    u32 sum;
    flash_unlock();
    while(i < 128) {
        sum = buf[i+3]<<24 | buf[i+2] << 16 | buf[i+1] << 8 | buf[i];
        flash_write_word(addr ,sum);
        addr += 4;
        i += 4;
    }   
    flash_lock();
}


void xmodem(void)
{
	unsigned char buff[10];
	int buff_cont = 0;
	int try = NAK_CONT;
	unsigned char block = 1;	
	int app_addr = APP_START_ADD;
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
		if (xmodem_data_check(block, xmodem_buff))
			fputc(NAK);
		else {
			xmodem_write_flash(app_addr, &(xmodem_buff[3]));
			fputc(ACK);
			app_addr += 128;
			block++;
		}
		xmodem_cont = 0;
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


