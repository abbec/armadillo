#include <stdint.h>


volatile unsigned int * const UART0DR = (unsigned int *)0x101f1000;

typedef unsigned long vaddr_t;
typedef unsigned long paddr_t;
typedef unsigned long pde_t;

/* Reserve space for a page directory. Must be 16k aligned. */
pde_t __attribute__((aligned(16384))) page_directory[1 << 12];

/* Create a 1MB mapping in the given page directory from 'virt' to 'phys'. */
void set_large_page_mapping(pde_t *pd, vaddr_t virt, paddr_t phys)
{
	pde_t entry = 0;
	entry |= phys & 0xfff00000; /* Target of the mapping. */
	entry |= 2;                 /* This is a 1MB section entry. */
	entry |= 1 << 4;            /* Enable caches (C). */
	entry |= 1 << 3;            /* Enable writeback (B). */
	entry |= 3 << 10;           /* Full read/write permission. */
	pd[virt >> 20] = entry;     /* Install the entry. */
}

void enable_mmu(pde_t *pd)
{
	uint32_t reg;

	// todo: move to separate asm file

	// copy page table address to cp15
	asm volatile("mcr p15, 0, %0, c2, c0, 0" : : "r" (pd) : "memory");

	// Set the access control to all-supervisor
	asm volatile("mcr p15, 0, %0, c3, c0, 0" : : "r" (~0));

	// Enable the MMU
	asm("mrc p15, 0, %0, c1, c0, 0" : "=r" (reg) : : "cc");
	reg |= 0x1;
	asm volatile("mcr p15, 0, %0, c1, c0, 0" : : "r" (reg) : "cc");
}

void setup_one_to_one_mappings()
{
	unsigned long i;

	// Setup a mapping for each 1MB region in the virtual address space
	for (i = 0; i < (1 << 12); i++) {
		// Map the virtual address "i << 20" to phys address "i << 20"
		set_large_page_mapping(page_directory, i << 20, i << 20);
	}

	enable_mmu(page_directory);
}

void print_serial(const char *s) {
	while(*s != '\0') { /* Loop until end of string */
		*UART0DR = (unsigned int)(*s); /* Transmit char */
		s++; /* Next char */
	}
}

void kmain() {
	print_serial("Hello Armadillo!\n");
	print_serial("Setting up MMU...\n");
	setup_one_to_one_mappings();

	int *x = (int *) 0x1234;
	*x = 0xdead;
	print_serial("done!\n");
}


