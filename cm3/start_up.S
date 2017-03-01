

.syntax unified
        .cpu cortex-m3
        .fpu softvfp
        .thumb

.global Reset_Handler

Reset_Handler:
	ldr 	r0,=100

