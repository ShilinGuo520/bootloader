# MCU name and submodel
MCU      = cortex-m3
SUBMDL   = stm32f103

TARGET = bootloader

# toolchain (using code sourcery now)
THUMB    = -mthumb
THUMB_IW = -mthumb-interwork

LDFLAGS += -T./cm3/bootloader.lds -Mmap > map.txt


#//////////compile tools///////////////////////
CROSS_COMPILE ?= arm-none-eabi-
CC       := $(CROSS_COMPILE)gcc
CXX      := $(CROSS_COMPILE)g++
LD       := $(CROSS_COMPILE)ld -v
AR       := $(CROSS_COMPILE)ar
AS       := $(CROSS_COMPILE)gcc
OBJCOPY  := $(CROSS_COMPILE)objcopy
OBJDUMP  := $(CROSS_COMPILE)objdump
SIZE     := $(CROSS_COMPILE)size


INC = -I./inc
CFLAGS =$(THUMB) -O0 -g3 -gdwarf-2 -nostdlib -ffunction-sections -fdata-sections -Wl,--gc-sections $(INC)
ASFLAGS = -x assembler-with-cpp


bootloader:
	$(AS) $(ASFLAGS) -o start_up.o -c ./cm3/start_up.S
	$(CC) $(CFLAGS) -o main.o -c ./common/main.c
	$(CC) $(CFLAGS) -o leds.o -c ./driver/leds.c
	$(LD) $(LDFLAGS) start_up.o leds.o main.o --output $(TARGET).elf
	$(OBJCOPY) -O binary $(TARGET).elf $(TARGET).bin
	$(OBJDUMP) -h -S -D $(TARGET).elf > objdump.txt

clean:
	rm *.o *.elf *.bin *.txt
