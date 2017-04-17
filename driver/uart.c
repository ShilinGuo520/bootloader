/***********************************************
 * uart driver
 ***********************************************/
#include "uart.h"
#include "gpio.h"
#include "rcc.h"
#include "nvic.h"
#include "glib.h"

#define EN_UART1_RX 1

struct ringbuffer {
	char *buff;
	int size;
	int data_num;
	int read;
	int write;
};

unsigned char uart_rx_buff[1024];

struct ringbuffer *uart_rx;

void ringbuffer_init(struct ringbuffer *rbuff, unsigned char *buff)
{
	rbuff->size = sizeof(buff);
	rbuff->buff = buff;
	rbuff->data_num = 0;
	rbuff->read = 0;
	rbuff->read = 0;
}

void ringbuffer_write(struct ringbuffer *rbuff, unsigned char ch)
{
	rbuff->buff[rbuff->write++] = ch;
	if(rbuff->write >= rbuff->size)
		rbuff->write = 0;

	rbuff->data_num++;
}

int ringbuffer_read(struct ringbuffer *rbuff, unsigned char *buff)
{
	int num = 0;
	if((rbuff->data_num) > 0) {
		*buff++ = rbuff->buff[rbuff->read++];
		if(rbuff->read >= rbuff->size)
			rbuff->read = 0;

		rbuff->data_num--;
		num++;
	}
	return num;
}


void uart_rx_buff_init(void)
{
	memset(uart_rx_buff, 0, sizeof(uart_rx_buff));
	ringbuffer_init(uart_rx, uart_rx_buff);
}


int uart_get_buff(unsigned char *buff)
{
	return ringbuffer_read(uart_rx ,buff);
}


int fputc(unsigned char ch)
{      
	while((USART1->SR&0X40)==0); //Blocking send
		USART1->DR = (unsigned char) ch;
	return ch;
}


int fputs(unsigned char *ch)
{
	while(*ch != '\0')
		fputc(*ch++);
	return 0;
}

static void usart_enable_ISR(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = TRUE;
    nvicInit(&NVIC_InitStructure);
}

void uart_init(unsigned int pclk2,unsigned int bound)
{
	float temp;
	unsigned short mantissa;
	unsigned short fraction;	   
	temp = (float)(pclk2*1000000)/(bound*16);
	mantissa = temp;				 
	fraction = (temp-mantissa)*16;
    mantissa<<=4;
	mantissa += fraction; 
	RCC->APB2ENR |= 1<<2;
	RCC->APB2ENR |= 1<<14;
	GPIOA->CRH &= 0XFFFFF00F;
	GPIOA->CRH |= 0X000008B0;
		  
	RCC->APB2RSTR |= 1<<14;
	RCC->APB2RSTR &= ~(1<<14);

 	USART1->BRR = mantissa;
	USART1->CR1 |= 0X200C;
#if EN_UART1_RX
	USART1->CR1 |= 1 << 8;
	USART1->CR1 |= 1 << 5;
	uart_rx_buff_init();
	usart_enable_ISR();
#endif
}



#if EN_UART1_RX
void USART1_IRQHandler(void)
{	
	unsigned char res = 0;
	if(USART1->SR & (1 << 5)) {
		res = USART1->DR;
		ringbuffer_write(uart_rx, res);
//		USART1->DR = res;
	}
}
#endif
