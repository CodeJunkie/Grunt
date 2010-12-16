OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386)

ENTRY(start)

SECTIONS{
    . = 0x00100000;

    .text :{
        *(.text)
    }

    .rodata : {
        *(.rodata)
    }

    .data : {
        *(.data)
    }

    .bss : {
        sbss = .;
        *(COMMON)
        *(.bss)
        ebss = .;
    }
}

