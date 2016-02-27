ENTRY(_start)

__kern_phys_base = 0x100000;
__kern_virt_base = 0xf0400000;

__kern_offset = (__kern_virt_base - __kern_phys_base);

SECTIONS
{
	. = __kern_phys_base;
	__bootstrap_start = .;
	__start = .;
	.bootstrap_text : { *(.bootkernel) *init.c.obj(.text) }
	__bootstrap_end_text = .;

	.bootstrap_data ALIGN(4096) : { *init.c.obj(.data .rodata*) *boot.s.obj(.data .rodata*) }
	__bootstrap_end_data = .;

	.bootstrap_bss ALIGN(4096) : { *init.c.obj(.bss COMMON) *boot.s.obj(.bss COMMON) }
	__bootstrap_end = .;

	. += __kern_offset;
	. = ALIGN(4096);

	.text : AT(ADDR(.text) - __kern_offset) { *(.text*) }
	__end_text = .;
	__unpaged_end_text = . - __kern_offset;

	.data ALIGN(4096) : AT(ADDR(.data) - __kern_offset) { *(.data .rodata* ) }
	. = ALIGN(4096);
	__end_data = .;
	__unpaged_end_data = . - __kern_offset;

	.bss ALIGN(4096) : AT(ADDR(.bss) - __kern_offset) {
		*(.bss* COMMON)
		__unpaged_kern_size = . - __kern_virt_base;
		__kern_size = __unpaged_kern_size;

		. += 4096;
	}
	__unpaged_end = . - __kern_offset;
	__end = .;
}
