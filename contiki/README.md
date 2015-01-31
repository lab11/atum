Atum - Contiki
==============

This folder contains code to make Atum a
[Contiki](https://github.com/contiki-os/contiki) platform. Contiki has active
support of the CC2538 and this platform adds on drivers for the FRAM and
RTC chips.

Installation
------------

To compile apps for Atum you need this repository, the main Contiki repository,
and the toolchain.

1. Install the compilers. See
[this](https://github.com/contiki-os/contiki/tree/master/platform/cc2538dk#install-a-toolchain)
for a link to the best compiler to use for the CC2538.
Note: You MUST install from the launchpad website, NOT mentor.

2. Clone the main contiki repository

        git clone https://github.com/contiki-os/contiki.git

3. Add the `/tools` directory in this folder to your path. This folder contains
a script for initializing the RTC with the current time. Something like:

        export PATH=$PATH:$HOME/git/atum/contiki/tools

4. Make sure the applications know where the main Contiki repository is.
Edit `apps/blink/Makefile` and make sure that `CONTIKI = ../../../../contiki`
actually points to where you cloned the Contiki repository.


Compiling an Application
------------------------

At this point compiling a Contiki application for atum
should be very straightforward.

    cd apps/blink
    make

If you wanted to use a different platform (say the CC2538 evm with the SmartRF06
board):

    make TARGET=cc2538dk


Loading the Application to Atum
-------------------------------

Assuming you are using the serial bootloader (pins GND, VCC, !RESET,
BOOTLOADER_CTRL, BOOTLOADER_TX, and BOOTLOADER_RX) you can use the wonderful
[BSL script from JelmerT](https://github.com/JelmerT/cc2538-bsl) by:

    make install

In the case of a permission error for /dev/ttyUSB0, add yourself to the dialout
group.


Errors
------

It's possible these steps will not work. A major reason why is that the CC2538
platform in Contiki is changing rapidly and often adds in new features that
won't compile until the Atum platform is similarly updated. If this happens,
please raise an issue on this repository so that I can fix it.
