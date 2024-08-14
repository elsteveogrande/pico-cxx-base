MEMORY {
    FLASH(rx) : ORIGIN = 0x10000000, LENGTH = 2048k
    RAM(rwx) : ORIGIN =  0x20000000, LENGTH = 256k
    SCRATCH_X(rwx) : ORIGIN = 0x20040000, LENGTH = 4k
    SCRATCH_Y(rwx) : ORIGIN = 0x20041000, LENGTH = 4k
}

ENTRY (_boot2)

SECTIONS {
    .boot2 : {
        __boot2_start__ = .;
        KEEP (*(.boot2))
        __boot2_end__ = .;
    } > FLASH
    ASSERT(__boot2_start__ == 0x10000000, "ERROR: boot2 not at start of flash")
    ASSERT(__boot2_end__ - __boot2_start__ <= 256, "ERROR: boot2 cannot exceed 256 in size")

    . = ALIGN(256);

    .text : {
        KEEP (*(.init))
        KEEP (*(.text*))
        KEEP (*(.fini))
        *(SORT(.ctors.*))
        KEEP (*(.ctors))
        *(SORT(.dtors.*))
        KEEP (*(.dtors))
    } > FLASH

    .data : {
        KEEP (*(vtable))
        KEEP (*(.rodata*))
        KEEP (*(.data*))
    } > FLASH

    .bss : {
        __bss_start = .;
        KEEP (*(.bss*))
        __bss_end = .;
    } > RAM
    ASSERT(__bss_end - __bss_start <= 4096,
        "ERROR: bss cannot exceed 4096 in size")
}
