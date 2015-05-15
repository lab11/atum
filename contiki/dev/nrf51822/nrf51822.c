/**
* \defgroup nrf51822
* @{
*/

#include "contiki.h"
#include "nrf51822.h"
#include "spi-arch.h"
#include "spi.h"
#include "dev/ssi.h"
#include "ioc.h"

/**
* \author Brad Campbell <bradjc@umich.edu>
*/

#define NRF51822_INT_PORT_NUM  GPIO_B_NUM
#define NRF51822_INT_PIN       6
#define NRF51822_INT_BASE      GPIO_PORT_TO_BASE(NRF51822_INT_PORT_NUM)
#define NRF51822_INT_MASK      GPIO_PIN_MASK(NRF51822_INT_PIN)

#define NRF51822_CS_N_PORT_NUM GPIO_B_NUM
#define NRF51822_CS_N_PIN      3


void nrf51822_interrupt(uint8_t port, uint8_t pin)
{
  uint16_t b;
  uint8_t buf[256];
  int i;

  leds_toggle(LEDS_RED);


  spi_set_mode(SSI_CR0_FRF_MOTOROLA, 0, 0, 8);

  SPI_CS_CLR(NRF51822_CS_N_PORT_NUM, NRF51822_CS_N_PIN);
clock_delay_usec(8);
  // READ_IRQ
  SPI_WRITE(0x01);
  SPI_FLUSH();

SPI_CS_SET(NRF51822_CS_N_PORT_NUM, NRF51822_CS_N_PIN);

clock_delay_usec(75);

  SPI_CS_CLR(NRF51822_CS_N_PORT_NUM, NRF51822_CS_N_PIN);
clock_delay_usec(8);



  SPI_READ(b);

  if (b == 0xFF) {
    // ERROR on the nrf51822 side. Skip this.

  } else {

    for (i=0; i<b; i++) {
      SPI_READ(buf[i]);
    }

  }


  SPI_CS_SET(NRF51822_CS_N_PORT_NUM, NRF51822_CS_N_PIN);


}

/**
 * \brief Initialize the nRF51822.
 */
void
nrf51822_init()
{
  // Setup interrupt from nRF51822
  GPIO_SOFTWARE_CONTROL(NRF51822_INT_BASE, NRF51822_INT_MASK);
  GPIO_SET_INPUT(NRF51822_INT_BASE, NRF51822_INT_MASK);
  GPIO_DETECT_EDGE(NRF51822_INT_BASE, NRF51822_INT_MASK);
  GPIO_TRIGGER_SINGLE_EDGE(NRF51822_INT_BASE, NRF51822_INT_MASK);
  GPIO_DETECT_RISING(NRF51822_INT_BASE, NRF51822_INT_MASK);
  GPIO_ENABLE_INTERRUPT(NRF51822_INT_BASE, NRF51822_INT_MASK);
  ioc_set_over(NRF51822_INT_PORT_NUM, 0, IOC_OVERRIDE_DIS);
  nvic_interrupt_enable(NVIC_INT_GPIO_PORT_B);
  gpio_register_callback(nrf51822_interrupt,
                         NRF51822_INT_PORT_NUM,
                         NRF51822_INT_PIN);


  spi_cs_init(NRF51822_CS_N_PORT_NUM, NRF51822_CS_N_PIN);
  SPI_CS_SET(NRF51822_CS_N_PORT_NUM, NRF51822_CS_N_PIN);
}


void nrf51822_get_all_advertisements () {
  //spi_set_mode(SSI_CR0_FRF_MOTOROLA, SSI_CR0_SPO, SSI_CR0_SPH, 8);
  spi_set_mode(SSI_CR0_FRF_MOTOROLA, 0, 0, 8);

  SPI_CS_CLR(NRF51822_CS_N_PORT_NUM, NRF51822_CS_N_PIN);
clock_delay_usec(8);

  // GET ADVERTISEMENTS
  SPI_WRITE(0x02);

  SPI_FLUSH();

  SPI_CS_SET(NRF51822_CS_N_PORT_NUM, NRF51822_CS_N_PIN);
}


// int
// fm25l04b_read(uint16_t address, uint16_t len, uint8_t *buf)
// {
//   uint16_t i;
//   uint16_t current_address = address;

//   spi_set_mode(SSI_CR0_FRF_MOTOROLA, SSI_CR0_SPO, SSI_CR0_SPH, 8);

//   SPI_CS_CLR(FM25L04B_CS_N_PORT_NUM, FM25L04B_CS_N_PIN);

//   /* Send the READ command and the address to the FRAM */
//   SPI_WRITE(FM25L04B_ADD_ADDRESS_BIT(current_address, FM25L04B_READ_COMMAND));
//   SPI_WRITE(current_address & 0xFF);

//   SPI_FLUSH();

//   for (i=0; i<len; i++) {
//     SPI_READ(buf[i]);
//   }

//   SPI_CS_SET(FM25L04B_CS_N_PORT_NUM, FM25L04B_CS_N_PIN);

//   return 0;
// }


// int
// fm25l04b_write(uint16_t address, uint16_t len, uint8_t *buf)
// {
//   uint16_t i;

//   spi_set_mode(SSI_CR0_FRF_MOTOROLA, SSI_CR0_SPO, SSI_CR0_SPH, 8);


//   SPI_CS_CLR(FM25L04B_CS_N_PORT_NUM, FM25L04B_CS_N_PIN);

//   /* Send the WRITE ENABLE command to allow writing to the FRAM */
//   SPI_WRITE(FM25L04B_WRITE_ENABLE_COMMAND);

//   SPI_CS_SET(FM25L04B_CS_N_PORT_NUM, FM25L04B_CS_N_PIN);
//   SPI_CS_CLR(FM25L04B_CS_N_PORT_NUM, FM25L04B_CS_N_PIN);

//   /* Send the WRITE command and the address to the FRAM */
//   SPI_WRITE(FM25L04B_ADD_ADDRESS_BIT(address, FM25L04B_WRITE_COMMAND));
//   SPI_WRITE(address & 0xFF);

//   /* Send the data to write */
//   for(i=0; i<len; i++) {
//     SPI_WRITE(buf[i]);
//   }

//   SPI_CS_SET(FM25L04B_CS_N_PORT_NUM, FM25L04B_CS_N_PIN);

//   return 0;
// }
