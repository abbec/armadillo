#include <stdint.h>
#include <print.h>
#include <vm.h>

extern char __kern_virt_base;


void kmain()
{
	print_init();
	vaddr_t kernel_base = (vaddr_t) &__kern_virt_base;
	kprintf("Hello Armadillo at 0x%x! Booting...\n", kernel_base);
}

