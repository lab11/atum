#include "app.h"
#include "contiki.h"
#include "cpu.h"
#include "dev/ioc.h"
#include "sys/etimer.h"
#include "sys/rtimer.h"
#include "dev/leds.h"
#include "dev/uart.h"
#include "dev/button-sensor.h"
#include "dev/watchdog.h"
#include "dev/serial-line.h"
#include "dev/sys-ctrl.h"
#include "net/rime/broadcast.h"
#include "net/ip/uip.h"
#include "net/ip/uip-udp-packet.h"
#include "net/ip/uiplib.h"
#include "net/ipv6/uip-ds6-route.h"
#include "net/ipv6/uip-ds6-nbr.h"
#include "adc.h"
#include "soc-adc.h"

#include <stdio.h>
#include <stdint.h>
/*---------------------------------------------------------------------------*/
#define LOOP_INTERVAL       CLOCK_SECOND
#define LEDS_OFF_HYSTERISIS (RTIMER_SECOND >> 1)
#define LEDS_PERIODIC       LEDS_YELLOW
#define LEDS_BUTTON         LEDS_RED
#define LEDS_SERIAL_IN      LEDS_ORANGE
#define LEDS_REBOOT         LEDS_ALL
#define LEDS_RF_RX          (LEDS_YELLOW | LEDS_ORANGE)
#define BROADCAST_CHANNEL   129
/*---------------------------------------------------------------------------*/

#define UIP_IP_BUF   ((struct uip_ip_hdr *)&uip_buf[UIP_LLH_LEN])
#define UIP_ICMP_BUF ((struct uip_icmp_hdr *)&uip_buf[uip_l2_l3_hdr_len])

static uip_ipaddr_t my_addr;
static uip_ipaddr_t dest_addr;
static uip_ipaddr_t bcast_ipaddr;
static uip_lladdr_t bcast_lladdr = {{0, 0, 0, 0, 0, 0, 0, 0}};
static struct uip_udp_conn *client_conn;

pkt_data_t pkt_data = {PROFILE_ID, DATA_TYPE, VERSION, 0, 0};
uint32_t seq_no = 0;

static struct etimer periodic_timer;

PROCESS(airflow_test_process, "Airflow Test Process");
AUTOSTART_PROCESSES(&airflow_test_process);

/*---------------------------------------------------------------------------*/
static void
send_handler(process_event_t ev, process_data_t data)
{
  seq_no++;
  pkt_data.seq_no = uip_htonl(seq_no);

  pkt_data.airflow = uip_htons(adc_get(SOC_ADC_ADCCON_CH_AIN3,
                                       SOC_ADC_ADCCON_REF_EXT_SINGLE,
                                       SOC_ADC_ADCCON_DIV_512));

  uip_udp_packet_send(client_conn, (uint8_t*) &pkt_data, sizeof(pkt_data_t));
  leds_toggle(LEDS_BLUE);
}

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(airflow_test_process, ev, data)
{

  PROCESS_BEGIN();


  GPIO_SOFTWARE_CONTROL(GPIO_A_BASE, GPIO_PIN_MASK(3));
  GPIO_SET_INPUT(GPIO_A_BASE, GPIO_PIN_MASK(3));
  ioc_set_over(GPIO_A_NUM, 3, IOC_OVERRIDE_ANA);

  adc_init();

  // Set the local address
  uip_ip6addr(&my_addr, 0, 0, 0, 0, 0, 0, 0, 0);
  uip_ds6_set_addr_iid(&my_addr, &uip_lladdr);
  uip_ds6_addr_add(&my_addr, 0, ADDR_MANUAL);

  // Setup the destination address
  uiplib_ipaddrconv(RECEIVER_ADDR, &dest_addr);

  // Add a "neighbor" for our custom route
  // Setup the default broadcast route
  uiplib_ipaddrconv(ADDR_ALL_ROUTERS, &bcast_ipaddr);
  uip_ds6_nbr_add(&bcast_ipaddr, &bcast_lladdr, 0, NBR_REACHABLE);
  uip_ds6_route_add(&dest_addr, 128, &bcast_ipaddr);

  // Setup a udp "connection"
  client_conn = udp_new(&dest_addr, UIP_HTONS(RECEIVER_PORT), NULL);
  if (client_conn == NULL) {
    // Too many udp connections
    // not sure how to exit...stupid contiki
  }
  udp_bind(client_conn, UIP_HTONS(3001));

  etimer_set(&periodic_timer, 10*CLOCK_SECOND);

  while(1) {
    PROCESS_YIELD();

    if (etimer_expired(&periodic_timer)) {
      send_handler(ev, data);
      etimer_restart(&periodic_timer);
    }
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/