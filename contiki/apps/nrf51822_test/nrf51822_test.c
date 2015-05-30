
#include "contiki.h"
#include "dev/leds.h"
#include "nrf51822.h"

#include <stdint.h>
#include <string.h>
#include <stdio.h>



/*---------------------------------------------------------------------------*/
PROCESS(nrf51822_test, "nRF51822 Test");
AUTOSTART_PROCESSES(&nrf51822_test);
/*---------------------------------------------------------------------------*/



PROCESS_THREAD(nrf51822_test, ev, data) {
	int i;

	PROCESS_BEGIN();

	leds_off(LEDS_ALL);

	nrf51822_init();
	nrf51822_get_all_advertisements();

	while(1) {
		PROCESS_YIELD();
	}

	PROCESS_END();
}
