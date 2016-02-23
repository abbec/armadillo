#pragma once

typedef unsigned long vaddr_t;
typedef unsigned long paddr_t;
typedef unsigned long pde_t;

#define SECTION_SHIFT 20
#define SECTION_MASK (~((1 << SECTION_SHIFT) - 1))
#define SECTION_SIZE (1024*1024)
#define VM_SECTION (1 << 1)
#define VM_SECTION_CACHED (1 << 4)
#define VM_SECTION_SUPER (1 << 10)
#define VM_SECTION_DOMAIN (15 << 5)
#define VM_SECTION_USER (3 << 10)

#define VM_SECTION_B (1 << 2)  /* B Bit */

#define VM_SECTION_DEVICE (VM_SECTION_B)

#define VM_ENTRIES 4096
