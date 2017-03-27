
MEMORY
{
    rom : ORIGIN = 0x00000000, LENGTH = 0x40000
    ram : ORIGIN = 0x20000000, LENGTH = 0x4000
}

SECTIONS
{
    .text : { *(.text*) } > rom
    .rodata : { *(.rodata*) } > rom
    .bss : { *(.bss*) } > ram
}

