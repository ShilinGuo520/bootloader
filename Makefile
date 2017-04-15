# MCU name and submodel
MCU      = cortex-m3
SUBMDL   = stm32f103

TARGET = bootloader

# toolchain (using code sourcery now)
THUMB    = -mthumb

#--------------compile tools-------------------
CROSS_COMPILE ?= arm-none-eabi-
CC       := $(CROSS_COMPILE)gcc
LD       := $(CROSS_COMPILE)ld -v
AS       := $(CROSS_COMPILE)gcc
AR		 := $(CROSS_COMPILE)ar
OBJCOPY  := $(CROSS_COMPILE)objcopy
OBJDUMP  := $(CROSS_COMPILE)objdump


INC = -I./inc
CFLAGS =$(THUMB) -O0 -g3 -gdwarf-2 -nostdlib -ffunction-sections -fdata-sections -Wl,--gc-sections $(INC)
ASFLAGS = -x assembler-with-cpp
LDFLAGS = -T./cm3/bootloader.ld -Mmap > map.txt
ARFLAGS = -rv


ALL_LIB = libcommon.a
ALL_LIB += libdriver.a

ALL_SRC = start_up.o $(ALL_LIB)


bootloader:$(ALL_SRC)
	$(LD) $(LDFLAGS) $(ALL_SRC) --output $(TARGET).elf
	$(OBJCOPY) -O binary $(TARGET).elf $(TARGET).bin
	$(OBJDUMP) -h -S -D $(TARGET).elf > objdump.txt


libcommon.a:
	$(MAKE) -C common

libdriver.a:
	$(MAKE) -C driver

start_up.o:
	$(AS) $(ASFLAGS) -o start_up.o -c ./cm3/start_up.S


clean:
	rm *.o *.a *.elf *.bin *.txt
	$(MAKE) clean -C common
	$(MAKE)	clean -C driver

