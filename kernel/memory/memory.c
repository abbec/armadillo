#include <memory.h>

void *memset(void *ptr, uint8_t value, uint32_t num)
{
	uint8_t *p = ptr;
	for (uint32_t i = 0; i < num; ++i)
	{
		*p = value;
		++p;
	}

	return ptr;
}
