

MEMORY
{
  RAM (xrw)     : ORIGIN = 0x20000000, LENGTH =  8K
  FLASH (rx)    : ORIGIN = 0x08000000, LENGTH = 20K
}

SECTIONS
{
	.text :
	{
		. = ALIGN(0x4);
		start_up.o(.text)
		*(.text*)
		*(.rodata)
		*(.rodata*)
		text_end = .;
	} > FLASH

	.data  : AT (text_end)
	{	
		. = ALIGN(0x4);
		data_start = .;
		*(.data)
		*(.data*)
	} > RAM
	data_size = SIZEOF(.data);	

	.bss : 
	{	
		. = ALIGN(0x4);
		bss_start = .;
		*(.bss)
		*(.bss*)
	} > RAM
	bss_size = SIZEOF(.bss);

	.stack :
	{
	} > RAM
	stack_top = 0x20000400;
}


