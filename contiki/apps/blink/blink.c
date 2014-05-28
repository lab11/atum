
#include "contiki.h"
#include "sys/etimer.h"
#include "dev/leds.h"

static struct etimer periodic_timer_red;
static struct etimer periodic_timer_green;
static struct etimer periodic_timer_blue;

/*---------------------------------------------------------------------------*/
PROCESS(blink_process, "Blink");
AUTOSTART_PROCESSES(&blink_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(blink_process, ev, data) {

	PROCESS_BEGIN();

	etimer_set(&periodic_timer_red, CLOCK_SECOND);
	etimer_set(&periodic_timer_green, CLOCK_SECOND/2);
	etimer_set(&periodic_timer_blue, CLOCK_SECOND/4);

	while(1) {
		PROCESS_YIELD();

		if (etimer_expired(&periodic_timer_red)) {
			leds_toggle(LEDS_RED);
			etimer_restart(&periodic_timer_red);
		} else if (etimer_expired(&periodic_timer_green)) {
			leds_toggle(LEDS_GREEN);
			etimer_restart(&periodic_timer_green);
		} else if (etimer_expired(&periodic_timer_blue)) {
			leds_toggle(LEDS_BLUE);
			etimer_restart(&periodic_timer_blue);
		}
	}

	PROCESS_END();
}
