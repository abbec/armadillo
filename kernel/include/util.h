#pragma once
#include <stdint.h>

extern void dummy();

static void delay(int32_t cycles)
{
	for (uint32_t i=0, end = cycles; i < end; ++i)
	{
		dummy();
	}
}
