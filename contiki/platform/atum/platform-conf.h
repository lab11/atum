/**
 * \addtogroup cc2538
 * @{
 *
 * \file
 *  Configuration for the atum platform
 */
#ifndef PLATFORM_CONF_H_
#define PLATFORM_CONF_H_

#include <stdint.h>
#include <string.h>


/* Enable external 32 kHz crystal */
#define SYS_CTRL_CONF_OSC32K_USE_XTAL 1

#define STARTUP_CONF_LEDS 0

/** @} */
/*---------------------------------------------------------------------------*/
/**
 * \name Serial Boot Loader Backdoor configuration
 *
 * @{
 */
#ifndef FLASH_CCA_CONF_BOOTLDR_BACKDOOR
#define FLASH_CCA_CONF_BOOTLDR_BACKDOOR	1 /**<Enable the boot loader backdoor */
#endif

#ifndef FLASH_CCA_CONF_BOOTLDR_BACKDOOR_PORT_A_PIN
#define FLASH_CCA_CONF_BOOTLDR_BACKDOOR_PORT_A_PIN 2 /**< Pin PA_2 activates the boot loader */
#endif

#ifndef FLASH_CCA_CONF_BOOTLDR_BACKDOOR_ACTIVE_HIGH
#define FLASH_CCA_CONF_BOOTLDR_BACKDOOR_ACTIVE_HIGH 0 /**< A logic low level activates the boot loader */
#endif

#ifndef STARTUP_CONF_VERBOSE
#define STARTUP_CONF_VERBOSE        0 /**< Set to 0 to decrease startup verbosity */
#endif

#ifndef IEEE802154_CONF_PANID
#define IEEE802154_CONF_PANID           0x0022 /**< Default PAN ID: TinyOS */
#endif


#endif /* CONTIKI_CONF_H_ */

/** @} */
