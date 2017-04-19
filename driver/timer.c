/*****************************************
file name:timer.c
date:2017-04-19
*****************************************/
#include "timer.h"
#include "glib.h"
#include "rcc.h"

void timer_init(u16 arr ,u16 psc)
{
    u32 rwmVal;
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Enable timer3 clock */
    RCC->APB1ENR |= 1 << 1;
    /* Set arr */
    TIM3->ARR = arr;
    TIM3->PSC = psc;

    TIM3->DIER |= 1 << 0;
    TIM3->CR1 |= 0x01;

    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = TRUE;
    nvicInit(&NVIC_InitStructure);
}

int time_out_03;

void set_time_out(int time)
{
	time_out_03 = time;
}

bool get_time_out()
{
	return time_out_03;
}

void delay_ms(int time)
{
    set_time_out(time);
    while(get_time_out())
        ;   
}

void TIM3_IRQHandler(void)
{
    u32 rwmVal;
    rwmVal = TIM3->SR;
    if(rwmVal & 0x0001) {
		if(time_out_03 > 0)
			time_out_03--;
    }
    rwmVal &=~(1 << 0);
    TIM3->SR = rwmVal;
}

