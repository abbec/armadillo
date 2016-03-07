.section ".bootkernel"

// Make _start global.
.globl _start

// Entry point for the kernel.
_start:
	// Setup the stack.
	ldr sp, =load_stack_start
	mov fp, #0

	// Call pre init
	bl pre_init

	// Kernel is mapped high
	ldr sp, =stacktop
	mov r1, #0
	push {r1}

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

