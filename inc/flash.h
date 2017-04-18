#include "common.h"
#include "types.h"

#define FLASH_R_BASE	(AHBPERIPH_BASE + 0x2000)

#define FLASH_KEY1     0x45670123
#define FLASH_KEY2     0xCDEF89AB
#define FLASH_RDPRT    0x00A5
#define FLASH_SR_BSY   0x01
#define FLASH_CR_PER   0x02
#define FLASH_CR_PG    0x01
#define FLASH_CR_START 0x40

typedef struct
{
	volatile unsigned int ACR;
	volatile unsigned int KEYR;
	volatile unsigned int OPTKEYR;
	volatile unsigned int SR;
	volatile unsigned int CR;
	volatile unsigned int AR;
	volatile unsigned int RESERVED;
	volatile unsigned int OBR;
	volatile unsigned int WRPR;
	unsigned int RESERVED1[8]; 
	volatile unsigned int KEYR2;
	unsigned int RESERVED2;   
	volatile unsigned int SR2;
	volatile unsigned int CR2;
	volatile unsigned int AR2; 
} FLASH_TypeDef;


#define FLASH               ((FLASH_TypeDef *) FLASH_R_BASE)


extern void flash_lock();
extern void flash_unlock();
extern bool flash_erase_page(u32 pageAddr);
extern bool flash_erase_pages(u32 pageAddr, u16 n);
extern bool flash_write_word(u32 addr, u32 word);


