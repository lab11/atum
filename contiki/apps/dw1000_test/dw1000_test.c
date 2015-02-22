
#include "contiki.h"
#include "dev/leds.h"
#include "deca_device_api.h"

#include <stdint.h>
#include <string.h>
#include <stdio.h>

typedef struct {
	uint8_t  a;
	uint8_t  b;
	uint16_t c;
	uint32_t d;
} fram_test_t;

/*---------------------------------------------------------------------------*/
PROCESS(dw1000_test, "DW1000Test");
AUTOSTART_PROCESSES(&dw1000_test);
/*---------------------------------------------------------------------------*/

fram_test_t fram_data = {10, 50, 45982, 73652091};
fram_test_t* fram_data_read;

uint8_t buf[100] = {144};

PROCESS_THREAD(dw1000_test, ev, data) {
	int i;

	PROCESS_BEGIN();

	leds_off(LEDS_ALL);

	dw1000_init();

	dwt_initialise(0);

	dwt_getpartid();

	// memset(buf, 144, 100);

	// // Read the FRAM starting at 0
	// fm25l04b_read(0, sizeof(fram_test_t), buf);
	// //fm25l04b_read(0, 10, buf);

	// // Check if matches
	// fram_data_read = (fram_test_t*) buf;

	// for (i=0; i<20; i++) {
	// 	printf("buf%i: %u\n", i, buf[i]);
	// }

	// //if (buf[0] == 10) {
	// 	//leds_on(LEDS_GREEN);
	// //} else
	// if (memcmp(buf, &fram_data, sizeof(fram_test_t)) == 0) {
	// 	// Hooray, FRAM works!
	// 	leds_on(LEDS_BLUE);
	// } else {
	// 	// Didn't match, let's try writing it first
	// 	fm25l04b_write(0, sizeof(fram_test_t), (uint8_t*) &fram_data);
	// 	leds_on(LEDS_RED);
	// }

	while(1) {
		PROCESS_YIELD();
	}

	PROCESS_END();
}
