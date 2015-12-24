#include <liquid/liquid.h>
#include "radio_util.h"
#include "radio.h"
#include "greatest.h"


SUITE_EXTERN(dsss);
SUITE_EXTERN(util);

GREATEST_MAIN_DEFS();

int main (int argc, char ** argv)
{
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(dsss);
    RUN_SUITE(util);

    GREATEST_MAIN_END();
}
