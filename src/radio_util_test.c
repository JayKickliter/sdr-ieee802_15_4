#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <inttypes.h>

#include "greatest.h"
#include "radio.h"
#include "radio_dsss.h"
#include "radio_util.h"
#include <liquid/liquid.h>

SUITE(util);

TEST test_flip_bits()
{
    uint32_t ref, val;

    for(size_t i = 0; i <= 32; ++i)
    {
        ref = (uint32_t) rand();
        val = radio_flip_bits(ref, i);
        ASSERT_EQ(i, count_bit_errors(ref, val));
    }
    PASS();
}

SUITE(util)
{
    RUN_TEST(test_flip_bits);
}
