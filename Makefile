# MCU name and submodel
MCU      = cortex-m3
SUBMDL   = stm32f103

TARGET = bootloader

# toolchain (using code sourcery now)
THUMB    = -mthumb
THUMB_IW = -mthumb-interwork

LDFLAGS += -T./cm3/bootloader.lds -Mmap > map.txt


#//////////compile tools///////////////////////
CROSS_COMPILE ?= arm-none-linux-gnueabi-
CC       := $(CROSS_COMPILE)gcc
CXX      := $(CROSS_COMPILE)g++
LD       := $(CROSS_COMPILE)ld -v
AR       := $(CROSS_COMPILE)ar
AS       := $(CROSS_COMPILE)gcc
OBJCOPY  := $(CROSS_COMPILE)objcopy
OBJDUMP  := $(CROSS_COMPILE)objdump
SIZE     := $(CROSS_COMPILE)size

CFLAGS = -Os -g3 -gdwarf-2 -nostdlib -ffunction-sections -fdata-sections -Wl,--gc-sections
ASFLAGS = -x assembler-with-cpp
SRC = main.o


ALL_CFLAGS  = -mcpu=$(MCU) $(THUMB_IW) -I. $(CFLAGS)



bootloader:
	$(AS) $(ASFLAGS) -o start_up.o -c ./cm3/start_up.S
	$(CC) $(CFLAGS) -o main.o -c ./common/main.c
	$(LD) $(LDFLAGS) main.o start_up.o --output $(TARGET).elf
	$(OBJCOPY) -O binary $(TARGET).elf $(TARGET).bin
	$(OBJDUMP) -h -S -D $(TARGET).elf > objdump.txt
	
.o.c:
	$(CC) $(CFLAGS) -o $@ -c $<
.o.S:
	$(AS) $(ASFLAGS) -o $@ -c $<

clean:
	rm *.o *.elf *.bin *.txt
