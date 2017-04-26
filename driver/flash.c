#include "flash.h"
#include "types.h"
#include "glib.h"

#define FLASH_LOG_EN	0

bool flash_erase_page(u32 pageAddr) {
#if FLASH_LOG_EN
	printf("%s:erase addr:0x%08x\r\n", __func__, pageAddr);
#endif
    u32 rwmVal = FLASH->CR;
    rwmVal = FLASH_CR_PER;
    FLASH->CR = rwmVal;

    while (FLASH->SR & FLASH_SR_BSY) {}
    FLASH->AR = pageAddr;
    FLASH->CR = (FLASH_CR_START | FLASH_CR_PER);
    while (FLASH->SR & FLASH_SR_BSY) {}

    /* todo: verify the page was erased */

    rwmVal = 0x00;
    FLASH->CR = rwmVal;

    return TRUE;
}
bool flash_erase_pages(u32 pageAddr, u16 n) {
#if FLASH_LOG_EN
	printf("%s:star:0x%08x cont:0x%08x \r\n", __func__, pageAddr, n);
#endif
    while (n-- > 0) {
        if (!flash_erase_page(pageAddr + 0x400 * n)) {
            return FALSE;
        }
    }

    return TRUE;
}



void flash_lock() {
    /* take down the HSI oscillator? it may be in use elsewhere */

    /* ensure all FPEC functions disabled and lock the FPEC */
	FLASH->CR = 0x00000080;
}

void flash_unlock() {
    /* unlock the flash */
	FLASH->KEYR = FLASH_KEY1;
	FLASH->KEYR = FLASH_KEY2;
}


bool flash_write_word(u32 addr, u32 word) {
    vu16 *flashAddr = (vu16 *)addr;
    vu32 lhWord = (vu32)word & 0x0000FFFF;
    vu32 hhWord = ((vu32)word & 0xFFFF0000) >> 16;

    u32 rwmVal = FLASH->CR;
    FLASH->CR = FLASH_CR_PG;
    /* apparently we need not write to FLASH_AR and can
       simply do a native write of a half word */
    while (FLASH->SR & FLASH_SR_BSY) {}
    *(flashAddr + 0x01) = (vu16)hhWord;
    while (FLASH->SR & FLASH_SR_BSY) {}
    *(flashAddr) = (vu16)lhWord;
    while (FLASH->SR & FLASH_SR_BSY) {}

    rwmVal &= 0xFFFFFFFE;
    FLASH->CR = rwmVal;

    /* verify the write */
    if (*(vu32 *)addr != word) {
#if FLASH_LOG_EN
	printf("%s addr:0x%08x word:0x%08x err\r\n", addr, word);
#endif
        return FALSE;
    }

    return TRUE;
}


