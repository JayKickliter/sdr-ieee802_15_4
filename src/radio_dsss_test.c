#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <inttypes.h>

#include "greatest.h"
#include "radio.h"
#include "radio_dsss.h"
#include "radio_util.h"

SUITE(dsss);

TEST chip_seq_lookup(struct radio_dsss * obj, uint32_t chips,
                     uint8_t ref_symbol)
{
    enum radio_status status;
    uint8_t           symbol;
    uint32_t          chips_with_errors;

    status = radio_dsss_map_chips_to_symbol(obj, chips, &symbol);
    ASSERT_EQ(radio_status_ok, status);
    ASSERT_EQ_FMT(ref_symbol, symbol, "%" PRIu8);

    /* Make sure we can decode a chip sequence with chip_error_threshold bit
     * errors */
    chips_with_errors = radio_flip_bits(chips, obj->chip_error_threshold);
    status = radio_dsss_map_chips_to_symbol(obj, chips_with_errors, &symbol);
    ASSERT_EQ(radio_status_ok, status);
    ASSERT_EQ_FMT(ref_symbol, symbol, "%" PRIu8);

    /* Make sure a chip sequence with > chip_error_threshold bit errors fails */
    chips_with_errors = radio_flip_bits(chips, obj->chip_error_threshold+1);
    status = radio_dsss_map_chips_to_symbol(obj, chips_with_errors, &symbol);
    ASSERT_EQ(radio_status_no_match, status);

    PASS();
}

SUITE(dsss)
{
    struct radio_dsss obj;
    uint32_t          chips;
    uint8_t           ref_symbol;

    /* Test BPSK DSSS lookup */
    radio_dsss_init(&obj, 0, radio_mod_type_dbpsk);
    for (size_t i = 0; i < obj.chip_map.length; ++i)
    {
        chips      = obj.chip_map.chips[i];
        ref_symbol = obj.chip_map.symbols[i];
        RUN_TESTp(chip_seq_lookup, &obj, chips, ref_symbol);
    }

    /* Test OQPSK DSSS lookup */
    radio_dsss_init(&obj, 0, radio_mod_type_oqpsk);
    for (size_t i = 0; i < obj.chip_map.length; ++i)
    {
        chips      = obj.chip_map.chips[i];
        ref_symbol = obj.chip_map.symbols[i];
        RUN_TESTp(chip_seq_lookup, &obj, chips, ref_symbol);
    }
}
