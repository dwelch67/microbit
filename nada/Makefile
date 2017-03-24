
ARMGNU = arm-none-eabi
#ARMGNU = arm-linux-gnueabi

AOPS = --warn --fatal-warnings -mcpu=cortex-m0
COPS = -Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding  -mcpu=cortex-m0


all : nada.bin 

clean:
	rm -f *.bin
	rm -f *.o
	rm -f *.elf
	rm -f *.list

#---------------------------------

flash.o : flash.s
	$(ARMGNU)-as $(AOPS) flash.s -o flash.o

nada.bin : flash.ld flash.o 
	$(ARMGNU)-ld -o nada.elf -T flash.ld flash.o
	$(ARMGNU)-objdump -D nada.elf > nada.list
	$(ARMGNU)-objcopy nada.elf nada.bin -O binary

