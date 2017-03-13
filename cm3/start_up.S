
	.syntax unified
	.cpu cortex-m3
	.fpu softvfp
	.thumb


__Vectors:
	.word stack_top
	.word 0x080000ed
	.word	0 //NMI_Handler
	.word	0 //HardFault_Handler
	.word	0 //MemManage_Handler
	.word	0 //BusFault_Handler
	.word	0 //UsageFault_Handler
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0 //SVC_Handler
	.word	0 //DebugMon_Handler
	.word	0
	.word	0 //PendSV_Handler
	.word	0 //SysTick_Handler
	.word	0 //WWDG_IRQHandler
	.word	0 //PVD_IRQHandler
	.word	0 //TAMPER_IRQHandler
	.word	0 //RTC_IRQHandler
	.word	0 //FLASH_IRQHandler
	.word	0 //RCC_IRQHandler
	.word	0 //EXTI0_IRQHandler
	.word	0 //EXTI1_IRQHandler
	.word	0 //EXTI2_IRQHandler
	.word	0 //EXTI3_IRQHandler
	.word	0 //EXTI4_IRQHandler
	.word	0 //DMA1_Channel1_IRQHandler
	.word	0 //DMA1_Channel2_IRQHandler
	.word	0 //DMA1_Channel3_IRQHandler
	.word	0 //DMA1_Channel4_IRQHandler
	.word	0 //DMA1_Channel5_IRQHandler
	.word	0 //DMA1_Channel6_IRQHandler
	.word	0 //DMA1_Channel7_IRQHandler
	.word	0 //ADC1_2_IRQHandler
	.word	0 //USB_HP_CAN1_TX_IRQHandler
	.word	0 //USB_LP_CAN1_RX0_IRQHandler
	.word	0 //CAN1_RX1_IRQHandler
	.word	0 //CAN1_SCE_IRQHandler
	.word	0 //EXTI9_5_IRQHandler
	.word	0 //TIM1_BRK_IRQHandler
	.word	0 //TIM1_UP_IRQHandler
	.word	0 //TIM1_TRG_COM_IRQHandler
	.word	0 //TIM1_CC_IRQHandler
	.word	0 //TIM2_IRQHandler
	.word	0 //TIM3_IRQHandler
	.word	0 //TIM4_IRQHandler
	.word	0 //I2C1_EV_IRQHandler
	.word	0 //I2C1_ER_IRQHandler
	.word	0 //I2C2_EV_IRQHandler
	.word	0 //I2C2_ER_IRQHandler
	.word	0 //SPI1_IRQHandler
	.word	0 //SPI2_IRQHandler
	.word	0 //USART1_IRQHandler
	.word	0 //USART2_IRQHandler
	.word	0 //USART3_IRQHandler
	.word	0 //EXTI15_10_IRQHandler
	.word	0 //RTCAlarm_IRQHandler
	.word	0 //USBWakeUp_IRQHandler


Reset_Handler:
Copy_data_to_ram:
	ldr r0,=data_start
	ldr r1,=data_size
	ldr r2,=text_end
lop_copy_data:
	ldr r3,[r2],#4
	str r3,[r0],#4
	sub r1,r1,#4
	bmi lop_copy_data

Clear_bss:
	ldr r0,=bss_start
	ldr r1,=bss_size
	mov r2,#0
lop_clear_bss:
	str r2,[r0],#4
	sub r1,r1,#4
	bmi lop_clear_bss

	b	main
