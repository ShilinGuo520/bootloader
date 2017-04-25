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


void xmodem(void)
{
	printf("\n\rfile:%s func:%s line:%d \n\r", __FILE__, __func__, __LINE__);
	
}


