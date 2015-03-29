Programming Atum
================

The software for Atum is currently based on the Contiki support for
the TI CC2538. Getting running is pretty straightforward.

1. You need the `arm-none-gnueabi-gcc` compiler from
[here](https://launchpad.net/gcc-arm-embedded).

2. Clone Contiki recursively.

        git clone --recursive https://github.com/contiki-os/contiki.git

    Cloning recursively also pulls in the BSL programming script that loads
    code on the CC2538.

3. Now you should be able to build the blink app.

        cd contiki/apps/blink
        make

    You need to make sure that `CONTIKI` in the Makefile points to where
    you cloned the Contiki repository.
