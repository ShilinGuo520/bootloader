# MCU name and submodel
MCU      = cortex-m3
SUBMDL   = stm32f103

TARGET = libdriver.a
SRC = clk.o leds.o uart.o nvic.o flash.o timer.o

# toolchain (using code sourcery now)
THUMB    = -mthumb
THUMB_IW = -mthumb-interwork

#--------------compile tools-------------------
CROSS_COMPILE ?= arm-none-eabi-
CC       := $(CROSS_COMPILE)gcc
AR		 := $(CROSS_COMPILE)ar


INC = -I./../inc
CFLAGS =$(THUMB) $(THUMB_IW) -O2 -g3 -gdwarf-2 -nostdlib -ffunction-sections -fdata-sections -Wl,--gc-sections -fno-builtin $(INC)
ARFLAGS = -rv


$(TARGET):$(SRC)
	$(AR) $(ARFLAGS) $(TARGET) $(SRC)
	mv $(TARGET) ../


%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f *.o
