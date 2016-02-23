#include <print_serial.h>

// TODO: this cannot be hardcoded
volatile unsigned int * const UART0DR = (unsigned int *)0x101f1000;
void serial_putc(char c)
{
	*UART0DR = (unsigned int)(c);
}

