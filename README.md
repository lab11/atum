Atum
====

![atum_pcb](https://raw.github.com/lab11/atum/master/media/atum_a_500x496.jpg)

Atum is a ½ inch² drop-in sensor node module designed to enable rapid
prototyping of wireless embedded devices. The core of Atum is a CC2538
SoC with an Arm Cortex M3 and 802.15.4 radio. Atum also includes an
antenna, 512 bytes of non-volatile FRAM memory, an RTC, and a tri-color LED.

Atum is designed to have two different usage patterns. First, three sides
of the device have castellated headers allowing Atum to be directly
soldered onto a carrier PCB. Atum handles all of the computation and
communication while the carrier board supplies power and attaches
sensors or other peripherals. In the second option, Atum can function
as a complete sensor node. On the bottom are pads for a 3.3 V regulator
and a battery. If needed, a peripheral or sensor board can be stacked on
top using the headers as a bridge.


History
-------

Atum is the spiritual successor to
[Epic](http://www.cs.berkeley.edu/~prabal/projects/epic/). It is slightly
smaller, replaces flash with FRAM, adds an RTC, and includes an antenna.
Epic was designed to be highly flexible while still providing the
components that are common on many sensor platforms. In practice, however,
I noticed that only a small subset of the common features were regularly
used and that Epic carrier boards often repeated the same designs. Atum
tries to address this by providing a simplified interface that provides
the features (e.g. SPI, I2C, ADC, GPIO) that sensor boards need.

Name
----

The spelling "Atum" is taken from the ancient Egyptian god of creation,
but finds better connections as a misspelling of "atom", a core building
block of matter, and as the conjoined words "at" and "UM", as Atum
was developed at the University of Michigan.

Usage
-----

The [Contiki](https://github.com/contiki-os/contiki) operating system
supports the CC2538 and this repository contains a Contiki platform
for Atum. The Contiki platform provides drivers for the peripherals
on Atum and their wiring to the CC2538. See `CONTIKI.md` for more info.

PCB
---

Atum is currently pannelized 40 to a panel. They are designed to be 1mm thick
with castellations on the edge. See `hardware/atum` for board files and
gerbers.


