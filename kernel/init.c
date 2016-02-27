#include <stdint.h>
#include <vm.h>
#include <memory.h>

extern char __kern_phys_base;
extern char __kern_virt_base;
extern char __kern_size;
static paddr_t kernel_start = (paddr_t) &__kern_phys_base;
static paddr_t kernel_size = (paddr_t) &__kern_size;

// bss segments
extern char __bootstrap_end_data;
extern char __bootstrap_end;

extern char __unpaged_end_data;
extern char __unpaged_end;

// Reserve space for a page directory. Must be 16k aligned.
pde_t __attribute__((aligned(16384))) page_directory[VM_ENTRIES];

void set_pd(pde_t *pd)
{
	// copy page table address to cp15
	asm volatile("mcr p15, 0, %0, c2, c0, 0" : : "r" (pd) : "memory");
}

void enable_mmu()
{
	uint32_t reg;

	// Set the access control to all-supervisor
	asm volatile("mcr p15, 0, %0, c3, c0, 0" : : "r" (~0));

	// Enable the MMU
	asm("mrc p15, 0, %0, c1, c0, 0" : "=r" (reg) : : "cc");
	reg |= 0x1;
	asm volatile("mcr p15, 0, %0, c1, c0, 0" : : "r" (reg) : "cc");
}

void setup_one_to_one_mappings(pde_t *pd)
{
	for (uint32_t i = 0; i < VM_ENTRIES; i++) {
		paddr_t p = i * SECTION_SIZE;
		pd[i] = p
			| VM_SECTION
			| VM_SECTION_USER
			| VM_SECTION_DOMAIN
			| VM_SECTION_CACHED;
	}
}

vaddr_t map_kernel(pde_t *pd)
{
	const vaddr_t kernel_virt = (vaddr_t) &__kern_virt_base;
	paddr_t kernel_phys = kernel_start;

	// find out which directory entry the
	// kernel should go into
	pde_t pde = kernel_virt / SECTION_SIZE;

	// map directories
	uint32_t mapped = 0;
	while (mapped < kernel_size) {

		pd[pde] = (kernel_phys & SECTION_MASK)
			| VM_SECTION
			| VM_SECTION_SUPER
			| VM_SECTION_DOMAIN
			| VM_SECTION_CACHED;


		mapped += SECTION_SIZE;
		kernel_phys += SECTION_SIZE;
		++pde;
	}

	return kernel_virt;
}

void pre_init()
{
	// clear bss (both temp bootstrap one
	// and future kernel one).
	// Need to use physical addresses (unpaged)
	// here since the MMU is not set up yet
	memset(&__unpaged_end_data, 0,
			(uint32_t)&__unpaged_end -
			(uint32_t)&__unpaged_end_data);

	memset(&__bootstrap_end_data, 0,
			(uint32_t)&__bootstrap_end -
			(uint32_t)&__bootstrap_end_data);

	// this code needs to stay where it is
	setup_one_to_one_mappings(page_directory);

	// map the kernel high where it
	// expects to be
	map_kernel(page_directory);

	// set the newly initialized page directory
	set_pd(page_directory);

	// enable the mmu
	enable_mmu();
}
