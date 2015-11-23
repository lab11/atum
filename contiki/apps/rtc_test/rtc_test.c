
#include "contiki.h"
#include "dev/leds.h"
#include "rv3049.h"

#include <stdint.h>
#include <string.h>
#include <stdio.h>


/*---------------------------------------------------------------------------*/
PROCESS(rtc_test, "RTC Test");
AUTOSTART_PROCESSES(&rtc_test);
/*---------------------------------------------------------------------------*/

static struct etimer periodic_timer_rtc;

rv3049_time_t rtctime;
uint8_t last_seconds = 0;


PROCESS_THREAD(rtc_test, ev, data) {

	PROCESS_BEGIN();

	leds_off(LEDS_ALL);

	etimer_set(&periodic_timer_rtc, CLOCK_SECOND*5);


	while(1) {
		PROCESS_YIELD();
		if (etimer_expired(&periodic_timer_rtc)) {

			rv3049_read_time(&rtctime);

			if (rtctime.seconds - 3 >  last_seconds) {
				leds_toggle(LEDS_BLUE);
				leds_off(LEDS_RED);
			} else {
				leds_toggle(LEDS_RED);
				leds_off(LEDS_BLUE);
			}
			last_seconds = rtctime.seconds;
			etimer_restart(&periodic_timer_rtc);
		}
	}

	PROCESS_END();
}
