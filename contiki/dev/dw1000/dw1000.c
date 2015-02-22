
#include "contiki.h"
#include "spi-arch.h"
#include "spi.h"
#include "dev/ssi.h"
#include "dev/leds.h"

void
dw1000_init()
{
  spi_cs_init(DW1000_CS_N_PORT_NUM, DW1000_CS_N_PIN);
  SPI_CS_SET(DW1000_CS_N_PORT_NUM, DW1000_CS_N_PIN);
}

int readfromspi(uint16_t headerLength,
                const uint8_t *headerBuffer,
                uint32_t readlength,
                uint8_t *readBuffer) {
  int i;

  // spi_set_mode(SSI_CR0_FRF_MOTOROLA, SSI_CR0_SPO, SSI_CR0_SPH, 8);
  spi_set_mode(SSI_CR0_FRF_MOTOROLA, 0, 0, 8);

  SPI_CS_CLR(DW1000_CS_N_PORT_NUM, DW1000_CS_N_PIN);

  leds_on(LEDS_RED);
  leds_on(LEDS_GREEN);

  for (i=0; i<headerLength; i++) {
    SPI_WRITE(headerBuffer[i]);
  }

  SPI_FLUSH();

  for (i=0; i<readlength; i++) {
    SPI_READ(readBuffer[i]);
  }

  SPI_CS_SET(DW1000_CS_N_PORT_NUM, DW1000_CS_N_PIN);

  return 0;

}

int writetospi(uint16_t headerLength,
               const uint8_t *headerBuffer,
               uint32_t bodylength,
               const uint8_t *bodyBuffer) {
  int i;

  // spi_set_mode(SSI_CR0_FRF_MOTOROLA, SSI_CR0_SPO, SSI_CR0_SPH, 8);
  spi_set_mode(SSI_CR0_FRF_MOTOROLA, 0, 0, 8);
  SPI_CS_CLR(DW1000_CS_N_PORT_NUM, DW1000_CS_N_PIN);

  for (i=0; i<headerLength; i++) {
    SPI_WRITE(headerBuffer[i]);
  }

  for (i=0; i<bodylength; i++) {
    SPI_WRITE(bodyBuffer[i]);
  }

  SPI_CS_SET(DW1000_CS_N_PORT_NUM, DW1000_CS_N_PIN);

  return 0;
}

void usleep (int microseconds) {
  clock_delay_usec(microseconds);
}

