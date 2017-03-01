

Reset_Handler:
	ldr 	sp,=0x20008000
	ldr	r0,=main
	bx	r0
