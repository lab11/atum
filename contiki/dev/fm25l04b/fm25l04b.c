/**
* \defgroup fm25l04b
* @{
*/

#include "contiki.h"
#include "fm25l04b.h"
#include "spi-arch.h"
#include "spi.h"
#include "dev/ssi.h"

/**
* \file   Driver for the FM25L04B series of flash chips
* \author Brad Campbell <bradjc@umich.edu>
*/

/**
 * \brief Initialize the FM25L04B.
 */
void
fm25l04b_init()
{
  /* Set the HOLD_N and WP_N pins to outputs and high */
  GPIO_SET_OUTPUT(GPIO_PORT_TO_BASE(FM25L04B_HOLD_N_PORT_NUM),
                  GPIO_PIN_MASK(FM25L04B_HOLD_N_PIN));
  GPIO_SET_OUTPUT(GPIO_PORT_TO_BASE(FM25L04B_WP_N_PORT_NUM),
                  GPIO_PIN_MASK(FM25L04B_WP_N_PIN));
  GPIO_SOFTWARE_CONTROL(GPIO_PORT_TO_BASE(FM25L04B_HOLD_N_PORT_NUM),
                        GPIO_PIN_MASK(FM25L04B_HOLD_N_PIN));
  GPIO_SOFTWARE_CONTROL(GPIO_PORT_TO_BASE(FM25L04B_WP_N_PORT_NUM),
                        GPIO_PIN_MASK(FM25L04B_WP_N_PIN));
  GPIO_SET_PIN(GPIO_PORT_TO_BASE(FM25L04B_HOLD_N_PORT_NUM),
               GPIO_PIN_MASK(FM25L04B_HOLD_N_PIN));
  GPIO_SET_PIN(GPIO_PORT_TO_BASE(FM25L04B_WP_N_PORT_NUM),
               GPIO_PIN_MASK(FM25L04B_WP_N_PIN));

  spi_cs_init(FM25L04B_CS_N_PORT_NUM, FM25L04B_CS_N_PIN);
  SPI_CS_SET(FM25L04B_CS_N_PORT_NUM, FM25L04B_CS_N_PIN);
}

/**
 * \brief         Read from the FRAM chip.
 * \param address The index of the byte to start reading from.
 * \param len     The number of bytes to read.
 * \param buf     A buffer to put the return data in.
 * \return        0 on success, -1 on error
 *
 *                Reads len bytes from the FRAM chip starting at address.
 */
int
fm25l04b_read(uint16_t address, uint16_t len, uint8_t *buf)
{
  uint16_t i;
  uint16_t current_address = address;

  spi_set_mode(SSI_CR0_FRF_MOTOROLA, SSI_CR0_SPO, SSI_CR0_SPH, 8);

  SPI_CS_CLR(FM25L04B_CS_N_PORT_NUM, FM25L04B_CS_N_PIN);

  /* Send the READ command and the address to the FRAM */
  SPI_WRITE(FM25L04B_ADD_ADDRESS_BIT(current_address, FM25L04B_READ_COMMAND));
  SPI_WRITE(current_address & 0xFF);

  SPI_FLUSH();

  for (i=0; i<len; i++) {
    SPI_READ(buf[i]);
  }

  SPI_CS_SET(FM25L04B_CS_N_PORT_NUM, FM25L04B_CS_N_PIN);

  return 0;
}

/**
 * \brief         Write to the FRAM chip.
 * \param address The index of the byte to start writing to.
 * \param len     The number of bytes to write.
 * \param buf     A buffer of values to write.
 * \return        0 on success, -1 on error
 *
 *                Writes len bytes to the FRAM chip starting at address.
 */
int
fm25l04b_write(uint16_t address, uint16_t len, uint8_t *buf)
{
  uint16_t i;

  spi_set_mode(SSI_CR0_FRF_MOTOROLA, SSI_CR0_SPO, SSI_CR0_SPH, 8);


  SPI_CS_CLR(FM25L04B_CS_N_PORT_NUM, FM25L04B_CS_N_PIN);

  /* Send the WRITE ENABLE command to allow writing to the FRAM */
  SPI_WRITE(FM25L04B_WRITE_ENABLE_COMMAND);

  SPI_CS_SET(FM25L04B_CS_N_PORT_NUM, FM25L04B_CS_N_PIN);
  SPI_CS_CLR(FM25L04B_CS_N_PORT_NUM, FM25L04B_CS_N_PIN);

  /* Send the WRITE command and the address to the FRAM */
  SPI_WRITE(FM25L04B_ADD_ADDRESS_BIT(address, FM25L04B_WRITE_COMMAND));
  SPI_WRITE(address & 0xFF);

  /* Send the data to write */
  for(i=0; i<len; i++) {
    SPI_WRITE(buf[i]);
  }

  SPI_CS_SET(FM25L04B_CS_N_PORT_NUM, FM25L04B_CS_N_PIN);

  return 0;
}
