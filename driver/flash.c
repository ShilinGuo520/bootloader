#include "flash.h"
#include "types.h"

void flash_lock() {
    /* take down the HSI oscillator? it may be in use elsewhere */

    /* ensure all FPEC functions disabled and lock the FPEC */
	FLASH->CR = 0x00000080;
}

void flash_unlock() {
    /* unlock the flash */
	FLASH->KEYR = FLASH_KEY1;
	FLASH->KEYR = FLASH_KEY1;
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
        return FALSE;
    }

    return TRUE;
}


