#ifndef RADIO_H_AE7891E1
#define RADIO_H_AE7891E1

#include <liquid/liquid.h>

enum radio_status
{
    radio_status_ok = 0,
    radio_status_err,
};

enum radio_band
{
    radio_band_low,
    radio_band_high,
};

enum radio_mod_type
{
    radio_mod_type_dbpsk,
    radio_mod_type_oqpsk,
};

struct radio_phy
{
    enum radio_band         band;
    struct modem_s *        tx_mod;
    struct modem_s *        rx_mod;
    struct symsync_crcf_s * rx_sync;
};

struct radio_ctx
{
    struct radio_phy phy_lb; /**< low-band PHY  */
    struct radio_phy phy_hb; /**< high-band PHY */
};

/** \brief Initialize a radio PHY
 * \param phy PHY to initialize
 * \param band high or low band
 * \return status
 */
enum radio_status radio_phy_init(struct radio_phy * const phy,
                                 enum radio_band band);

/** \brief Deallocate a PHY's members
 * \param phy PHY to initialize
 * \param band high or low band
 * \return status
 */
void radio_phy_destroy(struct radio_phy * const phy);

/** \brief Initialize a radio context
 * \param ctx context to initialize
 * \return status
 */
enum radio_status radio_ctx_init(struct radio_ctx * const ctx);

/** \brief Deallocate context's members
 * \param ctx context
 */
void radio_ctx_destroy(struct radio_ctx * const ctx);

#endif /* end of include guard: RADIO_H_AE7891E1 */
