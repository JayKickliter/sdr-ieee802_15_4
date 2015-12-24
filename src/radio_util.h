#ifndef SDR_UTIL_H_1ACD460E
#define SDR_UTIL_H_1ACD460E

#include <stdio.h>
#include <stdint.h>

#define NULLCHECK(PTR)                          \
do {                                            \
    if (NULL == PTR)                            \
    {                                           \
        fprintf(stderr, "[%s:%d] NULL == %s\n", \
                __func__,                       \
                __LINE__,                       \
                #PTR);                          \
    }                                           \
} while(0)


#define RS(STS)                                 \
do {                                            \
    if (radio_status_ok != STS)                 \
    {                                           \
        return STS;                             \
    }                                           \
} while(0)


uint32_t radio_flip_bits(uint32_t val, size_t bits_to_flip);


#endif /* end of include guard: SDR_UTIL_H_1ACD460E */
