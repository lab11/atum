#ifndef PROJECT_CONF_H_
#define PROJECT_CONF_H_

/*
 *
 * @author: Brad Campbell <bradjc@umich.edu>
 */

#define NETSTACK_CONF_RDC     nullrdc_driver
#define NETSTACK_CONF_MAC     nullmac_driver


// Shut the thing up
#define STARTUP_CONF_VERBOSE 1
//#define UART_CONF_ENABLE 0
//#define CC2538_CONF_QUIET 1


// Do not use some address set by the code, read it in from the magical info
// page on the cc2538
#define IEEE_ADDR_CONF_HARDCODED 0
#define IEEE_ADDR_CONF_USE_SECONDARY_LOCATION 1

// Set the RF channel and panid
// #define IEEE802154_CONF_PANID 0x689a
//#define IEEE802154_CONF_PANID 0xbbb1
//#define CC2538_RF_CONF_CHANNEL 20
#define IEEE802154_CONF_PANID 0x0022
//#define CC2538_RF_CONF_CHANNEL 19
#define CC2538_RF_CONF_CHANNEL 21



// RPL
// #define RPL_CONF_OF rpl_mrhof
#define RPL_CONF_OF rpl_of0

#define UIP_CONF_LOGGING 0



#endif /* PROJECT_CONF_H_ */

/** @} */
