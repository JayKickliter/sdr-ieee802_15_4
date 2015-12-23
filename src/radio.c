#include "radio.h"
#include "radio_util.h"

enum radio_status radio_ctx_init(struct radio_ctx * const ctx)
{
    RS(radio_phy_init(&ctx->phy_lb, radio_band_low));
    RS(radio_phy_init(&ctx->phy_hb, radio_band_high));
    return radio_status_ok;
}


void radio_ctx_destroy(struct radio_ctx * const ctx)
{
    radio_phy_destroy(&ctx->phy_lb);
    radio_phy_destroy(&ctx->phy_hb);
}


void radio_phy_destroy(struct radio_phy * const phy)
{
    modem_destroy(phy->tx_mod);
    modem_destroy(phy->rx_mod);
    symsync_crcf_destroy(phy->rx_sync);
}

enum radio_status radio_phy_init(struct radio_phy * const phy,
                                 enum radio_band band)
{
    switch (band)
    {
        case radio_band_low:
        phy->band = radio_band_low;
        phy->tx_mod = modem_create(LIQUID_MODEM_DPSK2);
        NULLCHECK(phy->tx_mod);
        phy->rx_mod = modem_create(LIQUID_MODEM_DPSK2);
        NULLCHECK(phy->rx_mod);
        break;

        case radio_band_high:
        phy->band = radio_band_high;
        break;
    }

    return radio_status_ok;
}
