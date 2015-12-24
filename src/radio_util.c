#include "radio_util.h"

uint32_t radio_flip_bits(uint32_t val, size_t bits_to_flip)
{
    if (bits_to_flip > sizeof(val)*8)
    {
        return val;
    }

    if (bits_to_flip == 0)
    {
        return val;
    }

    for(size_t i = 0; i < bits_to_flip; ++i)
    {
        val ^= 1 << i;
    }

    return val;
}
