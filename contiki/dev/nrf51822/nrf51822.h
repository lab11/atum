#ifndef NRF51822_H_
#define NRF51822_H_

void nrf51822_interrupt(uint8_t port, uint8_t pin);
void nrf51822_init();
void nrf51822_get_all_advertisements ();

#endif