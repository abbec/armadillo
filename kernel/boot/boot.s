.section ".bootkernel"

// Make _start global.
.globl _start

// Entry point for the kernel.
// r15 -> should begin execution at 0x8000.
// r0 -> 0x00000000
// r1 -> 0x00000C42
// r2 -> 0x00000100 - start of ATAGS
// preserve these registers as argument for kernel_main
_start:
	// Setup the stack.
	ldr sp, =load_stack_start
	mov fp, #0

	// Call pre init
	bl pre_init

	// Kernel is mapped high
	// TODO: setup stack
	ldr r3, =kmain
	blx r3

	// halt
halt:
	wfe
	b halt

.data
load_stack:
	.space 4096
load_stack_start:
