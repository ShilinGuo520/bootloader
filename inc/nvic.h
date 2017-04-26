#include "common.h"
#include "types.h"

#define SCS_BASE   ((u32)0xE000E000)
#define NVIC_BASE  (SCS_BASE + 0x0100)
#define SCB_BASE   (SCS_BASE + 0x0D00)

#define SCS      SCS_BASE
#define NVIC     (SCS+0x100)
#define SCB      (SCS+0xD00)
#define STK      (SCS+0x10) 

#define SCB_VTOR (SCB+0x08)
#define STK_CTRL (STK+0x00)


#define TIM2_IRQ    ((u8)0x1C)
#define TIM3_IRQ    ((u8)0x1D)
#define USART1_IRQ  ((u8)0x25)



typedef struct {
    unsigned char NVIC_IRQChannel;
    unsigned char NVIC_IRQChannelPreemptionPriority;
    unsigned char NVIC_IRQChannelSubPriority;
    bool NVIC_IRQChannelCmd; /* TRUE for enable */
} NVIC_InitTypeDef;


typedef struct {
    volatile unsigned int CPUID;
    volatile unsigned int ICSR;
    volatile unsigned int VTOR;
    volatile unsigned int AIRCR;
    volatile unsigned int SCR;
    volatile unsigned int CCR;
    volatile unsigned int SHPR[3];
    volatile unsigned int SHCSR;
    volatile unsigned int CFSR;
    volatile unsigned int HFSR;
    volatile unsigned int DFSR; 
    volatile unsigned int MMFAR;
    volatile unsigned int BFAR;
    volatile unsigned int AFSR;
} SCB_TypeDef;


typedef struct {
    volatile unsigned int ISER[2];
    unsigned int RESERVED0[30];
    volatile unsigned int ICER[2];
    unsigned int RESERVED1[30];
    volatile unsigned int ISPR[2];
    unsigned int RESERVED2[30];
    volatile unsigned int ICPR[2];
    unsigned int RESERVED3[30];
    volatile unsigned int IABR[2];
    unsigned int RESERVED4[62];
    volatile unsigned int IPR[15];
} NVIC_TypeDef;

extern void nvicInit(NVIC_InitTypeDef *NVIC_InitStruct);
extern void nvic_disable_interrupts(void);

