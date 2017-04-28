	.syntax unified
	.cpu cortex-m3
	.fpu softvfp
	.thumb

__Vectros:
	.word	stack_top
	.word	(Reset_Handler + 1)
	.word	NMI_Handler
	.word	HardFault_Handler
	.word	MemManage_Handler
	.word	BusFault_Handler
	.word	UsageFault_Handler
	.word	0
	.word	0
	.word	0
	.word	0
	.word	SVC_Handler
	.word	DebugMon_Handler
	.word	0
	.word	PendSV_Handler
	.word	SysTick_Handler
	.word	WWDG_IRQHandler
	.word	PVD_IRQHandler
	.word	TAMPER_IRQHandler
	.word	RTC_IRQHandler
	.word	FLASH_IRQHandler
	.word	RCC_IRQHandler
	.word	EXTI0_IRQHandler
	.word	EXTI1_IRQHandler
	.word	EXTI2_IRQHandler
	.word	EXTI3_IRQHandler
	.word	EXTI4_IRQHandler
	.word	DMA1_Channel1_IRQHandler
	.word	DMA1_Channel2_IRQHandler
	.word	DMA1_Channel3_IRQHandler
	.word	DMA1_Channel4_IRQHandler
	.word	DMA1_Channel5_IRQHandler
	.word	DMA1_Channel6_IRQHandler
	.word	DMA1_Channel7_IRQHandler
	.word	ADC1_2_IRQHandler
	.word	USB_HP_CAN1_TX_IRQHandler
	.word	USB_LP_CAN1_RX0_IRQHandler
	.word	CAN1_RX1_IRQHandler
	.word	CAN1_SCE_IRQHandler
	.word	EXTI9_5_IRQHandler
	.word	TIM1_BRK_IRQHandler
	.word	TIM1_UP_IRQHandler
	.word	TIM1_TRG_COM_IRQHandler
	.word	TIM1_CC_IRQHandler
	.word	TIM2_IRQHandler
	.word	TIM3_IRQHandler
	.word	TIM4_IRQHandler
	.word	I2C1_EV_IRQHandler
	.word	I2C1_ER_IRQHandler
	.word	I2C2_EV_IRQHandler
	.word	I2C2_ER_IRQHandler
	.word	SPI1_IRQHandler
	.word	SPI2_IRQHandler
	.word	USART1_IRQHandler
	.word	USART2_IRQHandler
	.word	USART3_IRQHandler
	.word	EXTI15_10_IRQHandler
	.word	RTCAlarm_IRQHandler
	.word	USBWakeUp_IRQHandler


.word	_sidata
.word	_sdata
.word	_edata
.word	_sbss
.word	_ebss


Reset_Handler:
  movs	r1, #0
  b	LoopCopyDataInit

CopyDataInit:
	ldr	r3, =_sidata
	ldr	r3, [r3, r1]
	str	r3, [r0, r1]
	adds	r1, r1, #4

LoopCopyDataInit:
	ldr	r0, =_sdata
	ldr	r3, =_edata
	adds	r2, r0, r1
	cmp	r2, r3
	bcc	CopyDataInit
	ldr	r2, =_sbss
	b	LoopFillZerobss
/* Zero fill the bss segment. */
FillZerobss:
	movs	r3, #0
	str	r3, [r2], #4

LoopFillZerobss:
	ldr	r3, = _ebss
	cmp	r2, r3
	bcc	FillZerobss


	bl	main


.globl __MSR_MSP
.thumb_func
__MSR_MSP:
    MSR msp, r0
    BX r14

	.weak	NMI_Handler
	.weak	HardFault_Handler
	.weak	MemManage_Handler
	.weak	BusFault_Handler
	.weak	UsageFault_Handler
	.weak	SVC_Handler
	.weak	DebugMon_Handler
	.weak	PendSV_Handler
	.weak	SysTick_Handler
	.weak	WWDG_IRQHandler
	.weak	PVD_IRQHandler
	.weak	TAMPER_IRQHandler
	.weak	RTC_IRQHandler
	.weak	FLASH_IRQHandler
	.weak	RCC_IRQHandler
	.weak	EXTI0_IRQHandler
	.weak	EXTI1_IRQHandler
	.weak	EXTI2_IRQHandler
	.weak	EXTI3_IRQHandler
	.weak	EXTI4_IRQHandler
	.weak	DMA1_Channel1_IRQHandler
	.weak	DMA1_Channel2_IRQHandler
	.weak	DMA1_Channel3_IRQHandler
	.weak	DMA1_Channel4_IRQHandler
	.weak	DMA1_Channel5_IRQHandler
	.weak	DMA1_Channel6_IRQHandler
	.weak	DMA1_Channel7_IRQHandler
	.weak	ADC1_2_IRQHandler
	.weak	USB_HP_CAN1_TX_IRQHandler
	.weak	USB_LP_CAN1_RX0_IRQHandler
	.weak	CAN1_RX1_IRQHandler
	.weak	CAN1_SCE_IRQHandler
	.weak	EXTI9_5_IRQHandler
	.weak	TIM1_BRK_IRQHandler
	.weak	TIM1_UP_IRQHandler
	.weak	TIM1_TRG_COM_IRQHandler
	.weak	TIM1_CC_IRQHandler
	.weak	TIM2_IRQHandler
	.weak	TIM3_IRQHandler
	.weak	TIM4_IRQHandler
	.weak	I2C1_EV_IRQHandler
	.weak	I2C1_ER_IRQHandler
	.weak	I2C2_EV_IRQHandler
	.weak	I2C2_ER_IRQHandler
	.weak	SPI1_IRQHandler
	.weak	SPI2_IRQHandler
	.weak	USART1_IRQHandler
	.weak	USART2_IRQHandler
	.weak	USART3_IRQHandler
	.weak	EXTI15_10_IRQHandler
	.weak	RTCAlarm_IRQHandler
	.weak	USBWakeUp_IRQHandler
