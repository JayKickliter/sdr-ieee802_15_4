#ifndef RADIO_DSSS_H_9FDF9CD9
#define RADIO_DSSS_H_9FDF9CD9

#include "radio.h"
#include <stdint.h>
#include <stdlib.h>

#define INVALID_SYMBOL 0xFF

struct radio_chip_map
{
    int chips_per_symbol; /**< 15 for BPSK, 32 for OQPSK */
    int bits_per_symbol;  /**< The number of bits a chip sequence represents */
    uint32_t mask;   /**< Mask for valid bit positions in chip sequence */
    size_t   length;      /**< The number of sequences in the map */
    uint8_t const *  restrict
                     symbols; /**< The bit values for individual symbols */
    uint32_t const * restrict chips; /**< The chip values */
};

/**
 * An object to represent a Direct Sequence Spread Spectrum
 * ([DSSS](https://en.wikipedia.org/wiki/Direct-sequence_spread_spectrum))
 *scheme
 **/
struct radio_dsss
{
    int chip_error_threshold; /**< Maximum allowable chip errors per symbol */
    struct radio_chip_map chip_map;
};

enum radio_status
radio_dsss_map_chips_to_symbol(struct radio_dsss const * restrict const obj,
                               uint32_t chips, uint8_t * restrict const symbol);

enum radio_status radio_dsss_init(struct radio_dsss * const obj,
                                  int chip_error_threshold,
                                  enum radio_mod_type);

#endif /* end of include guard: RADIO_DSSS_H_9FDF9CD9 */
