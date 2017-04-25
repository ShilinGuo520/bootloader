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


void xmodem(int argc)
{
	printf("file:%s\n\rfunc;%s\n\rline:%d", __FILE__, __func__, __LINE__);
}


