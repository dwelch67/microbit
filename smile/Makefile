f ?= /media/dan/MICROBIT/
CC = arm-none-eabi

ASMFLAGS = -mcpu=cortex-m0
CFLAGS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding -mcpu=cortex-m0

build: all clean

all:
	@$(CC)-as $(AOPS) flash.S -o flash.o
	@$(CC)-gcc $(COPS) -mthumb -c notmain.c -o notmain.o
	@$(CC)-ld -o notmain.elf -T flash.ld flash.o notmain.o
	@$(CC)-objdump -D notmain.elf > notmain.list
	@$(CC)-objcopy notmain.elf notmain.bin -O binary

	@cp notmain.bin /media/dan/MICROBIT/

clean:
	@rm -f *.bin *.o *.elf *.list
