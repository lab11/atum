/* Project configuration for the simple app where a packet is sent on wakeup
 * or periodically.
 *
 * @author: Brad Campbell <bradjc@umich.edu>
 */

#ifndef PROJECT_CONF_H_
#define PROJECT_CONF_H_

#define NETSTACK_CONF_RDC     nullrdc_driver

// Shut the thing up
//#define STARTUP_CONF_VERBOSE 0
//#define UART_CONF_ENABLE 0
//#define CC2538_CONF_QUIET 1

// IPv6 love
#define UIP_CONF_IPV6 1

// Do not use some address set by the code, read it in from the magical info
// page on the cc2538
#define IEEE_ADDR_CONF_HARDCODED 0

// Set the RF channel and panid
#define IEEE802154_CONF_PANID 0x0022
#define CC2538_RF_CONF_CHANNEL 24

// Don't need TCP
#define UIP_CONF_TCP 0
#define UIP_CONF_UDP 1

// a router, no rpl
#define UIP_CONF_ROUTER 1
#define UIP_CONF_IPV6_RPL 0

#define SICSLOWPAN_CONF_COMPRESSION_THRESHOLD 63
#define UIP_CONF_ND6_SEND_NA 0



#define UIP_CONF_LOGGING 0


#define SICSLOWPAN_CONF_ADDR_CONTEXT_0 {addr_contexts[0].prefix[0]=0;addr_contexts[0].prefix[1]=0;}









#endif /* PROJECT_CONF_H_ */

/** @} */
