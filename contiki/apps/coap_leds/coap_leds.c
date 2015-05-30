#include "contiki-net.h"
#include "contiki.h"
#include "cpu.h"
#include "sys/etimer.h"
#include "sys/rtimer.h"
#include "dev/leds.h"
#include "dev/uart.h"
#include "dev/watchdog.h"
#include "dev/serial-line.h"
#include "dev/sys-ctrl.h"
#include "net/rime/broadcast.h"
#include "net/ip/uip.h"
#include "net/ip/uip-udp-packet.h"
#include "net/ip/uiplib.h"
#include "net/ipv6/uip-ds6-route.h"
#include "net/ipv6/uip-ds6-nbr.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "rest-engine.h"


#define SW_VERSION "1.0"
#define HW_VERSION "A"


PROCESS(app, "CoAP LEDs app");
AUTOSTART_PROCESSES(&app);

int
coap_parse_bool (void* request)
{
  int length;
  const char* payload = NULL;

  length = REST.get_request_payload(request, (const uint8_t**) &payload);
  if (length > 0) {
    if (strncmp(payload, "true", length) == 0) {
      return 1;
    } else if (strncmp(payload, "false", length) == 0) {
      return 0;
    } else {
      return -1;
    }
  } else {
    return -1;
  }
}


/*******************************************************************************
 * led0/Power
 ******************************************************************************/

static void
led0_power_get_handler(void *request,
                       void *response,
                       uint8_t *buffer,
                       uint16_t preferred_size,
                       int32_t *offset) {
  int length;

  length = snprintf((char*) buffer, REST_MAX_CHUNK_SIZE, "%s",
    ((leds_get()&LEDS_GREEN)==LEDS_GREEN)?"true":"false");

  REST.set_header_content_type(response, REST.type.TEXT_PLAIN);
  REST.set_response_payload(response, buffer, length);
}

static void
led0_power_post_handler(void *request,
                  void *response,
                  uint8_t *buffer,
                  uint16_t preferred_size,
                  int32_t *offset) {

  uint8_t b = coap_parse_bool(request);
  if (b == 1) {
    leds_on(LEDS_GREEN);
  } else if (b == 0) {
    leds_off(LEDS_GREEN);
  } else {
    REST.set_response_status(response, REST.status.BAD_REQUEST);
  }
}

/* A simple actuator example. Toggles the red led */
RESOURCE(coap_led0_power,
         "title=\"Green LED\";rt=\"Control\"",
         led0_power_get_handler,
         led0_power_post_handler,
         led0_power_post_handler,
         NULL);


/*******************************************************************************
 * led1/Power
 ******************************************************************************/

static void
led1_power_get_handler(void *request,
                       void *response,
                       uint8_t *buffer,
                       uint16_t preferred_size,
                       int32_t *offset) {
  int length;

  length = snprintf((char*) buffer, REST_MAX_CHUNK_SIZE, "%s",
    ((leds_get()&LEDS_RED)==LEDS_RED)?"true":"false");

  REST.set_header_content_type(response, REST.type.TEXT_PLAIN);
  REST.set_response_payload(response, buffer, length);
}

static void
led1_power_post_handler(void *request,
                  void *response,
                  uint8_t *buffer,
                  uint16_t preferred_size,
                  int32_t *offset) {

  uint8_t b = coap_parse_bool(request);
  if (b == 1) {
    leds_on(LEDS_RED);
  } else if (b == 0) {
    leds_off(LEDS_RED);
  } else {
    REST.set_response_status(response, REST.status.BAD_REQUEST);
  }
}

/* A simple actuator example. Toggles the red led */
RESOURCE(coap_led1_power,
         "title=\"Red LED\";rt=\"Control\"",
         led1_power_get_handler,
         led1_power_post_handler,
         led1_power_post_handler,
         NULL);


/*******************************************************************************
 * led2/Power
 ******************************************************************************/

static void
led2_power_get_handler(void *request,
                       void *response,
                       uint8_t *buffer,
                       uint16_t preferred_size,
                       int32_t *offset) {
  int length;

  length = snprintf((char*) buffer, REST_MAX_CHUNK_SIZE, "%s",
    ((leds_get()&LEDS_BLUE)==LEDS_BLUE)?"true":"false");

  REST.set_header_content_type(response, REST.type.TEXT_PLAIN);
  REST.set_response_payload(response, buffer, length);
}

static void
led2_power_post_handler(void *request,
                  void *response,
                  uint8_t *buffer,
                  uint16_t preferred_size,
                  int32_t *offset) {

  uint8_t b = coap_parse_bool(request);
  if (b == 1) {
    leds_on(LEDS_BLUE);
  } else if (b == 0) {
    leds_off(LEDS_BLUE);
  } else {
    REST.set_response_status(response, REST.status.BAD_REQUEST);
  }
}

/* A simple actuator example. Toggles the red led */
RESOURCE(coap_led2_power,
         "title=\"Blue LED\";rt=\"Control\"",
         led2_power_get_handler,
         led2_power_post_handler,
         led2_power_post_handler,
         NULL);


/*******************************************************************************
 * device/software/Version
 ******************************************************************************/

static void
device_software_version_get_handler(void *request,
                  void *response,
                  uint8_t *buffer,
                  uint16_t preferred_size,
                  int32_t *offset) {
  int length;
  char res[] = "%s";

  length = snprintf((char*) buffer, REST_MAX_CHUNK_SIZE, res, SW_VERSION);

  REST.set_header_content_type(response, REST.type.TEXT_PLAIN);
  REST.set_response_payload(response, buffer, length);
}

RESOURCE(coap_device_software_version,
         "title=\"device/software/Version\";rt=\"sw\"",
         device_software_version_get_handler,
         NULL,
         NULL,
         NULL);


/*******************************************************************************
 * device/hardware/Version
 ******************************************************************************/

static void
device_hardware_version_get_handler(void *request,
                  void *response,
                  uint8_t *buffer,
                  uint16_t preferred_size,
                  int32_t *offset) {
  int length;
  char res[] = "%s";

  length = snprintf((char*) buffer, REST_MAX_CHUNK_SIZE, res, HW_VERSION);

  REST.set_header_content_type(response, REST.type.TEXT_PLAIN);
  REST.set_response_payload(response, buffer, length);
}

RESOURCE(coap_device_hardware_version,
         "title=\"device/hardware/Version\";rt=\"hw\"",
         device_hardware_version_get_handler,
         NULL,
         NULL,
         NULL);







PROCESS_THREAD(app, ev, data) {
  PROCESS_BEGIN();

  leds_on(LEDS_ALL);

  // CoAP + REST
  rest_init_engine();

  rest_activate_resource(&coap_led0_power,         "led0/Power");
  rest_activate_resource(&coap_led1_power,         "led1/Power");
  rest_activate_resource(&coap_led2_power,         "led2/Power");

  rest_activate_resource(&coap_device_software_version, "device/software/Version");
  rest_activate_resource(&coap_device_hardware_version, "device/hardware/Version");


  while (1) {
    PROCESS_WAIT_EVENT();
  }

  PROCESS_END();
}
