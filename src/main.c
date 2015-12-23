#include <liquid/liquid.h>
#include "radio_util.h"
#include "radio.h"

static modem modulator;
static modem demodulator;

int main (int argc, char const *argv[])
{
    modulator = modem_create(LIQUID_MODEM_DPSK2);
    NULLCHECK(modulator);

    demodulator = modem_create(LIQUID_MODEM_DPSK2);
    NULLCHECK(demodulator);

    out:
    modem_destroy(modulator);
    modem_destroy(demodulator);
    return 0;
}
