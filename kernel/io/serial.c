#include <stdint.h>
#include <stdbool.h>
#include <serial.h>
#include <bcm_2836.h>
#include <util.h>

#define ARM_TIMER_CTL   (PBASE+0x0000B408)
#define ARM_TIMER_CNT   (PBASE+0x0000B420)

#define GPFSEL1         (PBASE+0x00200004)
#define GPSET0          (PBASE+0x0020001C)
#define GPCLR0          (PBASE+0x00200028)
#define GPPUD           (PBASE+0x00200094)
#define GPPUDCLK0       (PBASE+0x00200098)

// UART 0 addresses
#define UART0_BASE   (PBASE+0x201000)
#define UART0_DR     (UART0_BASE+0x00)
#define UART0_RSRECR (UART0_BASE+0x04)
#define UART0_FR     (UART0_BASE+0x18)
#define UART0_ILPR   (UART0_BASE+0x20)
#define UART0_IBRD   (UART0_BASE+0x24)
#define UART0_FBRD   (UART0_BASE+0x28)
#define UART0_LCRH   (UART0_BASE+0x2C)
#define UART0_CR     (UART0_BASE+0x30)
#define UART0_IFLS   (UART0_BASE+0x34)
#define UART0_IMSC   (UART0_BASE+0x38)
#define UART0_RIS    (UART0_BASE+0x3C)
#define UART0_MIS    (UART0_BASE+0x40)
#define UART0_ICR    (UART0_BASE+0x44)
#define UART0_DMACR  (UART0_BASE+0x48)
#define UART0_ITCR   (UART0_BASE+0x80)
#define UART0_ITIP   (UART0_BASE+0x84)
#define UART0_ITOP   (UART0_BASE+0x88)
#define UART0_TDR    (UART0_BASE+0x8C)

static inline void mmio_write(uint32_t reg, uint32_t data)
{
	*(volatile uint32_t *)reg = data;
}

static inline uint32_t mmio_read(uint32_t reg)
{
	return *(volatile uint32_t *)reg;
}

void serial_init()
{
	// disable uart
	mmio_write(UART0_CR, 0x0);

	uint32_t ra = mmio_read(GPFSEL1);
	ra &= ~(7 << 12); //gpio14
	ra |= 4 << 12; //alt0
	ra &= ~(7 << 15); //gpio15
	ra |= 4 << 15; //alt0
	mmio_write(GPFSEL1, ra);

	mmio_write(GPPUD, 0x0);
	delay(150);

	mmio_write(GPPUDCLK0, (1 << 14) |( 1 << 15));
	delay(150);

	mmio_write(GPPUDCLK0, 0x0);

	mmio_write(UART0_ICR, 0x7ff);
	mmio_write(UART0_IBRD, 1);
	mmio_write(UART0_FBRD, 40);
	mmio_write(UART0_LCRH, 0x70);

	// enable uart again
	mmio_write(UART0_CR, 0x301);
}

void serial_putc(char c)
{
	while(mmio_read(UART0_FR) & 0x20) {}

	mmio_write(UART0_DR, c);
}

