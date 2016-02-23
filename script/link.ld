ENTRY(_start)

__kern_phys_base = 0x100000;
__kern_virt_base = 0xf0400000;

__kern_offset = (__kern_virt_base - __kern_phys_base);

SECTIONS
{
	. = __kern_phys_base;
	__unpaged_start = .;
	__start = .;
	.unpaged_text : { *(.bootkernel) *init.c.obj(.text) }

	.unpaged_data ALIGN(4096) : { *init.c.obj(.data .rodata*) *boot.s.obj(.data .rodata*) }
	.unpaged_bss ALIGN(4096) : { *init.c.obj(.bss COMMON) *boot.s.obj(.bss COMMON) }

	. += __kern_offset;

	. = ALIGN(4096); usermapped_start = .;
	.usermapped_glo : AT(ADDR(.usermapped_glo) - __kern_offset) { *(.usermapped_glo) }
	. = ALIGN(4096); usermapped_nonglo_start = .;
	.usermapped : AT(ADDR(.usermapped) - __kern_offset) { *(.usermapped) }
	. = ALIGN(4096); usermapped_end = .;
	.text             : AT(ADDR(.text) - __kern_offset) { *(.text*) }
	_etext = .;
	.data ALIGN(4096) : AT(ADDR(.data) - __kern_offset) { *(.data .rodata* ) }
	. = ALIGN(4096);
	_edata = .;
	__k_unpaged__edata = . - __kern_offset;
	.bss ALIGN(4096)  : AT(ADDR(.bss) - __kern_offset) { *(.bss* COMMON)
		__k_unpaged__kern_size = . - __kern_virt_base;
		__kern_size = __k_unpaged__kern_size;

		. += 4096;
	}
	__unpaged_end = . - __kern_offset;
	__end = .;
}
