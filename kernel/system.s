
.globl dummy
dummy:
    bx lr

.globl stacktop

.data
.balign 4
stack:
	.space 8192
stacktop:

