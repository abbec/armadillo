#include <print_serial.h>

// TODO: this cannot be hardcoded
volatile unsigned int * const UART0DR = (unsigned int *)0x101f1000;
void print_serial(const char *s)
{
	while(*s != '\0') {
		*UART0DR = (unsigned int)(*s);
		s++;
	}
}
