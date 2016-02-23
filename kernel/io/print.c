#include <print_serial.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

void putc(char c)
{
	serial_putc(c);

	// TODO: add console
}

void puts(const char *s)
{
	while (*s) {
		putc(*s);
		++s;
	}
}

void uitoa(uint32_t num, uint32_t base, bool uc, char * bf)
{
	int n=0;
	uint32_t d = 1;
	uint32_t a = num;
	while (a >= base) {
		d *= base;
		a = num/d;
	}	

	while (d != 0) {
		uint32_t dgt = num / d;
		num = num % d;
		d /= base;
		if (n || dgt > 0 || d == 0) {
			*bf = dgt+(dgt < 10 ? '0' : (uc ? 'A' : 'a') - 10);
			++bf;
			++n;
		}
	}

	*bf = '\0';
}

void itoa (int num, unsigned int base, char * bf)
{
	if (num<0) {
		num=-num;
		*bf++ = '-';
	}

	uitoa(num, base, false, bf);
}

/**
 * Super simple printf for the kernel
 */
void kprintf(const char *fmt, ...)
{
	va_list va;
	va_start(va,fmt);

	char c;
	char buffer[32];
	while ((c = *fmt)) {

		if (c != '%') {
			putc(c);
		} else {
			++fmt;
			c = *fmt;
			switch (c) {
				case 'x':
				case 'X':
					{
						uitoa(va_arg(va, uint32_t), 16, c == 'X', buffer);
						puts(buffer);
						break;
					}
				case 's':
					{
						const char *s = va_arg(va, char*);
						puts(s);
						break;
					}
				case 'd':
					{
						itoa(va_arg(va, int32_t), 10, buffer);
						puts(buffer);
						break;
					}
				case 'u':
					{
						uitoa(va_arg(va, uint32_t), 10, false, buffer);
						puts(buffer);
						break;
					}
			}
		}

		++fmt;
	}


	va_end(va);
}
