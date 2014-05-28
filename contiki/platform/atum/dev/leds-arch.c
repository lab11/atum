
#include "contiki.h"
#include "reg.h"
#include "dev/leds.h"
#include "dev/gpio.h"

/* Invert all of the leds because they are active low.
 */

#define LEDS_GPIO_PIN_MASK   LEDS_ALL
/*---------------------------------------------------------------------------*/
void
leds_arch_init(void)
{
	GPIO_SET_OUTPUT(LED_BLUE_BASE,  LED_BLUE_MASK);
	GPIO_SET_OUTPUT(LED_RED_BASE,   LED_RED_MASK);
	GPIO_SET_OUTPUT(LED_GREEN_BASE, LED_GREEN_MASK);
}
/*---------------------------------------------------------------------------*/
unsigned char
leds_arch_get(void)
{
	return ~(GPIO_READ_PIN(LED_BLUE_BASE,  LED_BLUE_MASK) |
	       GPIO_READ_PIN(LED_RED_BASE,   LED_RED_MASK) |
           GPIO_READ_PIN(LED_GREEN_BASE, LED_GREEN_MASK));
}
/*---------------------------------------------------------------------------*/
void
leds_arch_set(unsigned char leds)
{
	GPIO_WRITE_PIN(LED_BLUE_BASE,  LED_BLUE_MASK,  ~leds);
	GPIO_WRITE_PIN(LED_RED_BASE,   LED_RED_MASK,   ~leds);
	GPIO_WRITE_PIN(LED_GREEN_BASE, LED_GREEN_MASK, ~leds);
}
/*---------------------------------------------------------------------------*/

/**
 * @}
 * @}
 */
