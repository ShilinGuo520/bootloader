#include "common.h"
#include "types.h"
#include "leds.h"
#include "uart.h"
#include "clk.h"
#include "glib.h"
#include "flash.h"
#include "timer.h"

unsigned char data[100];
unsigned long num;

void wait_cmd(void);
void __MSR_MSP(u32 TopOfMainStack);

void info(void)
{
	printf("\n\rBuild Info:\n\rDate:%s\n\rTime:%s", __DATE__, __TIME__);
	printf("\n\rApp Start Add:%x", APP_START_ADD);
	printf("\n\rFlash Size:%d", FLASH_SIZE);
	printf("\n\rRam Size:%d\n\r", RAM_SIZE);
}

void erase_app(void)
{
    flash_unlock();

    if (flash_erase_pages(APP_START_ADD ,123) == TRUE) {
        printf("\r\nflash erase success\n\r");
    } else {
		printf("\r\nflash erase fail\r\n");
	}

    flash_lock();

}

void jump_to_app(void) {
	u32 usrAddr = APP_START_ADD;
    typedef void (*funcPtr)(void);

    u32 jumpAddr = *(vu32 *)(usrAddr + 0x04); /* reset ptr in vector table */
    funcPtr usrMain = (funcPtr) jumpAddr;

    /* tear down all the dfu related setup */
    // disable usb interrupts, clear them, turn off usb, set the disc pin
    // todo pick exactly what we want to do here, now its just a conservative
    flash_lock();
//    nvicDisableInterrupts();
//    systemReset(); // resets clocks and periphs, not core regs


    __MSR_MSP(*(vu32 *) usrAddr);             /* set the users stack ptr */

    usrMain();                                /* go! */
}

extern void xmodem(void);

int main()
{	
	unsigned char dec[10];
	unsigned long x,y;
	unsigned char buff[100];
	num = 10;

	sys_clk_init(9);

	uart_init(72, 115200); 	// 115200
	led_init(1);
	timer_init(100,719); // 10K 

	printf("Build Info:\n\rDate:%s\n\rTime:%s\n\r", __DATE__, __TIME__);

#if 0
	while(1) {
		delay_ms(500);
		led_on(1);
		delay_ms(500);
		led_off(1);
	}
#endif

#if 0	
	printf("flash test:\n\r");
	flash_unlock();

	if (flash_erase_pages(APP_START_ADD ,108) == TRUE) {
		printf("flash erase done\n\r");
	}
	flash_lock();
	
	flash_unlock();
	num = APP_START_ADD;
	y = 0;
	while (y < 0x1900) {
		if (flash_write_word(num, y) != TRUE) {
			printf("write err:0x%08x\n\r", num);
			break;
		}
		num = num + 4;
		y = y + 4;
	}
		
	if (y >= 0x1900) {
		printf("flash write done,flash test done\n\r");
	} else {
		printf("flash write err\n\r");
	}

	flash_lock();
#endif

	while(1) {
		wait_cmd();
	}

	return 0;
}

int get_cmd(unsigned char *cmd)
{
	char buff[15];
	int num = 0, i;
	memset(buff, 0, 15);
	while(1) {
		i = 0;
		i = uart_get_buff(&(buff[num]));
		if(i > 0) {
			if(buff[num + i - 1] == '\b') {
				if(num > 0) {
					fputs("\b \b");
					memset(&buff[--num], 0, i + 1);
				}
				continue;
			}
			fputs(&buff[num]);
			num += i;
			if((buff[num - 1] == 13) || (num >= 15))
				break;
		}
	}
	if(num >= 15) {
		return -1;
	} else {
		memcpy(cmd, buff, num - 1);
		return num;
	}
}

static struct {
	char *cmd;
	void (*func)(void);
	char *doc;
} command[] = {
	{"xmodem",				xmodem,				NULL},
	{"info",				info,				NULL},
	{"erase",				erase_app,			NULL},
	{"boot",				jump_to_app,		NULL},
	{NULL,					NULL,				NULL},	
};


void wait_cmd(void)
{
	char cmd_buf[15];
	int num = 0,i = 0;
	while(1) {
		memset(cmd_buf, 0, 15);
		num = get_cmd(cmd_buf);
		if(num > 0) {
			for(i = 0; command[i].cmd; i++) {
				if (strncmp(command[i].cmd, cmd_buf, strlen(command[i].cmd)))
					continue;
				command[i].func();
			}
		} else {
			printf("overflow\n\r");
		}
		printf("\n\r%s", CMD_TAG);
	}
	
}


