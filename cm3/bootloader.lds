

MEMORY
{
  RAM (xrw)     : ORIGIN = 0x20000000, LENGTH =  20K
  FLASH (rx)    : ORIGIN = 0x08000000, LENGTH = 128K
}

SECTIONS
{
	.text :
	{
		start_up.o(.text)
		*(.text*)
		*(.rodata)
		*(.rodata*)
		text_end = .;
	} > FLASH

	.data  : AT (text_end)
	{
		*(.data)
		*(.data*)
	} > RAM
	
	
	.bss : 
	{
		*(.bss)
		*(.bss*)
	} > RAM
	.stack :
	{
	} > RAM
}


