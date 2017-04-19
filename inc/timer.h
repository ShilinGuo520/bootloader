#include "common.h"
#include "types.h"
#include "nvic.h"



typedef struct
{
  volatile unsigned long CR1;
  volatile unsigned long CR2;
  volatile unsigned long SMCR;
  volatile unsigned long DIER;
  volatile unsigned long SR;
  volatile unsigned long EGR;
  volatile unsigned long CCMR1;
  volatile unsigned long CCMR2;
  volatile unsigned long CCER;
  volatile unsigned long CNT;
  volatile unsigned long PSC;
  volatile unsigned long ARR;
  volatile unsigned long RCR;
  volatile unsigned long CCR1;
  volatile unsigned long CCR2;
  volatile unsigned long CCR3;
  volatile unsigned long CCR4;
  volatile unsigned long BDTR;
  volatile unsigned long DCR;
  volatile unsigned long DMAR;
} TIM_TypeDef;


#define TIM1_BASE             (APB2PERIPH_BASE + 0x2C00)
#define TIM2_BASE             (APB1PERIPH_BASE + 0x0000)
#define TIM3_BASE             (APB1PERIPH_BASE + 0x0400)
#define TIM4_BASE             (APB1PERIPH_BASE + 0x0800)
#define TIM5_BASE             (APB1PERIPH_BASE + 0x0C00)
#define TIM6_BASE             (APB1PERIPH_BASE + 0x1000)
#define TIM7_BASE             (APB1PERIPH_BASE + 0x1400)
#define TIM8_BASE             (APB2PERIPH_BASE + 0x3400)
#define TIM12_BASE            (APB1PERIPH_BASE + 0x1800)
#define TIM13_BASE            (APB1PERIPH_BASE + 0x1C00)
#define TIM14_BASE            (APB1PERIPH_BASE + 0x2000)


#define TIM1				((TIM_TypeDef *) TIM1_BASE)
#define TIM2                ((TIM_TypeDef *) TIM2_BASE)
#define TIM3                ((TIM_TypeDef *) TIM3_BASE)
#define TIM4                ((TIM_TypeDef *) TIM4_BASE)
#define TIM5                ((TIM_TypeDef *) TIM5_BASE)
#define TIM6                ((TIM_TypeDef *) TIM6_BASE)
#define TIM7                ((TIM_TypeDef *) TIM7_BASE)
#define TIM8                ((TIM_TypeDef *) TIM8_BASE)
#define TIM12               ((TIM_TypeDef *) TIM12_BASE)
#define TIM13               ((TIM_TypeDef *) TIM13_BASE)
#define TIM14               ((TIM_TypeDef *) TIM14_BASE)

extern void timer_init(u16 arr ,u16 psc);
extern void set_time_out(int time);
extern bool get_time_out();
extern void delay_ms(int time);

