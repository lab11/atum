/**
 * \addtogroup atum
 * @{
 *
 * \file
 * Implementation of the atum specific functions
 */
#include "contiki.h"
#include "platform.h"
#include "spi.h"
#include "fm25l04b.h"
#include "rv3049.h"

/**
 * \brief Initialize peripherals.
 */
void
platform_init_post_initial()
{
  spi_init();
  fm25l04b_init();
  rv3049_init();
}

void
platform_init_post_networking()
{
}

void
platform_init_end()
{
}

/** @} */
