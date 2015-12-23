#ifndef SDR_UTIL_H_1ACD460E
#define SDR_UTIL_H_1ACD460E

#include <stdio.h>

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


#endif /* end of include guard: SDR_UTIL_H_1ACD460E */
