#include "common.h"

#define FLASH_R_BASE	(AHBPERIPH_BASE + 0x2000)

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


