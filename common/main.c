#include "common.h"
#include "types.h"
#include "leds.h"
#include "uart.h"
#include "clk.h"
#include "glib.h"
#include "flash.h"
#include "timer.h"


void help(void);
extern void xmodem(void);
extern void __MSR_MSP(u32 TopOfMainStack);

void info(void)
{
	printf("\n\rBuild Info:\n\rDate:%s\n\rTime:%s", __DATE__, __TIME__);
	printf("\n\rApp Start Add:%x", APP_START_ADD);
	printf("\n\rFlash Size:%d", FLASH_SIZE);
	printf("\n\rRam Size:%d\n\r", RAM_SIZE);
}

void erase_all_flash(void)
{
    flash_unlock();

    if (flash_erase_pages(APP_START_ADD ,123) == TRUE) {
        printf("\r\nflash erase success\n\r");
    } else {
		printf("\r\nflash erase fail\r\n");
	}

    flash_lock();

}

bool check_user_code(u32 usrAddr) {
    u32 sp = *(vu32 *) usrAddr;

    if ((sp & 0x2FFE0000) == 0x20000000) {
        return (TRUE);
    } else {
        return (FALSE);
    }   
}

void jump_to_app(void) 
{
	u32 usrAddr = APP_START_ADD;
    typedef void (*funcPtr)(void);

    u32 jumpAddr = *(vu32 *)(usrAddr + 0x04); /* reset ptr in vector table */
    funcPtr usrMain = (funcPtr) jumpAddr;

    flash_lock();
    nvic_disable_interrupts();


    __MSR_MSP(*(vu32 *) usrAddr);             /* set the users stack ptr */

    usrMain();                                /* go! */
}

void boot(void)
{
	if (check_user_code(APP_START_ADD))
		jump_to_app();
	else
		printf("\n\rnot find app code,boot fail \n\r");
}

void download(void)
{
	erase_all_flash();
	xmodem();
}


static struct {
    char *cmd;
    void (*func)(void);
    char *doc;
} command[] = {
	{"help",				help,				NULL},
    {"info",                info,               NULL},
    {"download",            download,           NULL},
    {"erase",               erase_all_flash,    NULL},
    {"boot",                boot,               NULL},
    {NULL,                  NULL,               NULL},  
};


void help(void)
{
	int i;
	printf("\n\rcommand line:\n\r");
	for (i = 0; command[i].cmd; i++) {
		printf(" %s \n\r", command[i].cmd);
        if (command[i].doc) {
            printf("--description:%s \n\r", command[i].doc);
        }
    }
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


int main()
{   
	unsigned char temp_buff[10];
    sys_clk_init(9);

    uart_init(72, 115200);  // 115200
    led_init(1);
    timer_init(100,719); // 10K 

    printf("Build Info:\n\rDate:%s\n\rTime:%s\n\r", __DATE__, __TIME__);

	set_time_out(BOOT_WAIT_TIME);	// Set boot wait time
	while(get_time_out()) {
		if (!(get_time_out()%1000)) {
			printf("\rwait time: %d s  ", (get_time_out()/1000));
		}
		
		if(uart_get_buff(temp_buff))
			goto wait;
	}

	printf("\n\rwait time out,try to boot the app.\n\r");
	boot();

wait:
	printf("\n\renter command mode\n\r");
    while(1) {
        wait_cmd();
    }

    return 0;
}

