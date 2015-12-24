#include "radio_dsss.h"
#include <stdint.h>
#include <limits.h>

static int const      chips_per_symbol_dbpsk = 15;
static int const      bits_per_symbol_dbpsk  = 1;
static size_t const   chip_map_length_dbpsk  = 2;
static uint32_t const chip_mask_dbpsk        = 0x00007fff;
static uint32_t const chip_map_dbpsk[]       = {0x000009af, 0x00007650};
static uint8_t const  symbol_map_dbpsk[]     = {0x00, 0x01};

static int const      chips_per_symbol_oqpsk = 32;
static int const      bits_per_symbol_oqpsk  = 4;
static size_t const   chip_map_length_oqpsk  = 16;
static uint32_t const chip_mask_oqpsk        = 0xffffffff;
static uint32_t const chip_map_oqpsk[]       = {
    0x6077ae6c, 0x4e077ae6, 0x6ce077ae, 0x66ce077a, 0x2e6ce077, 0x7ae6ce07,
    0x77ae6ce0, 0x077ae6ce, 0x1f885193, 0x31f88519, 0x131f8851, 0x1931f885,
    0x51931f88, 0x051931f8, 0x0851931f, 0x78851931};
static uint8_t const symbol_map_oqpsk[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
                                           0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b,
                                           0x0c, 0x0d, 0x0e, 0x0f};

enum radio_status
radio_dsss_map_chips_to_symbol(struct radio_dsss const * restrict const obj,
                               uint32_t chips, uint8_t * restrict const symbol)
{
    enum radio_status status       = radio_status_no_match;
    unsigned          min_errors   = UINT_MAX;
    uint8_t           symbol_match = UINT8_MAX;

    for (size_t i = 0; i < obj->chip_map.length; ++i)
    {
        unsigned errors = count_bit_errors(obj->chip_map.chips[i], chips);

        if (errors < min_errors && errors <= obj->chip_error_threshold)
        {
            status       = radio_status_ok;
            min_errors   = errors;
            symbol_match = obj->chip_map.symbols[i];
        }
    }

    *symbol = symbol_match;

    return status;
}

enum radio_status radio_dsss_init(struct radio_dsss * const obj,
                                  int                 chip_error_threshold,
                                  enum radio_mod_type mod_type)
{
    switch (mod_type)
    {
    case radio_mod_type_dbpsk:
        if (chip_error_threshold > chips_per_symbol_dbpsk)
        {
            return radio_status_invalid_parameter;
        }
        obj->chip_error_threshold      = chip_error_threshold;
        obj->chip_map.chips_per_symbol = chips_per_symbol_dbpsk;
        obj->chip_map.bits_per_symbol  = bits_per_symbol_dbpsk;
        obj->chip_map.mask             = chip_mask_dbpsk;
        obj->chip_map.length           = chip_map_length_dbpsk;
        obj->chip_map.symbols          = symbol_map_dbpsk;
        obj->chip_map.chips            = chip_map_dbpsk;
        break;

    case radio_mod_type_oqpsk:
        if (chip_error_threshold > chips_per_symbol_oqpsk)
        {
            return radio_status_invalid_parameter;
        }
        obj->chip_error_threshold      = chip_error_threshold;
        obj->chip_map.chips_per_symbol = chips_per_symbol_oqpsk;
        obj->chip_map.bits_per_symbol  = bits_per_symbol_oqpsk;
        obj->chip_map.mask             = chip_mask_oqpsk;
        obj->chip_map.length           = chip_map_length_oqpsk;
        obj->chip_map.symbols          = symbol_map_oqpsk;
        obj->chip_map.chips            = chip_map_oqpsk;
        break;
    }

    return radio_status_ok;
}
