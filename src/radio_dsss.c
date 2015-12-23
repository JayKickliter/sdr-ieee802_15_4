#include "radio_dsss.h"
#include <stdint.h>
#include <limits.h>

static uint16_t const bpsk_map[] = {0x09af, 0x7650};

static size_t count_chip_errors(uint32_t mask, uint32_t ref_chips,
                                uint32_t chips)
{
    return liquid_count_ones((chips & mask) ^ (ref_chips & mask));
}

uint8_t radio_dsss_map_chips_to_symbol(struct radio_dsss const * const obj,
                                       uint32_t chips)
{
    unsigned int min_errors = UINT_MAX;
    uint8_t      symbol     = INVALID_SYMBOL;

    for (size_t i = 0; i < obj->chip_map.map_length; ++i)
    {
        unsigned int errors = count_chip_errors(obj->chip_map.chip_mask,
                                                obj->chip_map.chips[i], chips);

        if (errors < min_errors && errors <= obj->chip_error_threshold)
        {
            symbol = obj->chip_map.symbols[i];
        }
    }

    return symbol;
}

enum radio_status radio_dsss_init(struct radio_dsss * const obj,
                                  int                 chip_error_threshold,
                                  enum radio_mod_type mod_type)
{
    return radio_status_ok;
}
