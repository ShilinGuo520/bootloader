

Reset_Handler:
	ldr sp,=stack_top


Copy_data_to_ram:
	ldr r0,=data_start
	ldr r1,=data_size
	ldr r2,=text_end
lop_copy_data:
	ldr r3,[r2],#4
	str r3,[r0],#4
	sub r1,r1,#4
	bne lop_copy_data


Clear_bss:
        ldr r0,=bss_start
        ldr r1,=bss_size
	mov r2,#0
lop_clear_bss:
	str r2,[r0],#4
	sub r1,r1,#4
	bne lop_clear_bss


        ldr r0,=main
        mov pc,r0 
	
