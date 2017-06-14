# bootloader

stm32f1xx boot

Instructions for use:

1.git clone thes project

2.install arm-none-eabi tools

3.make

4.used jtag download to flash(0x08000000)



bootloader jtag addr:0x08000000

application boot addr:0x08005000

cmd help:

download - used xmodem download app.bin to flash(0x08005000)

boot - boot app form flash(0x08005000)
