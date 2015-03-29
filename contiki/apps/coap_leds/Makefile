DEFINES+=PROJECT_CONF_H=\"project-conf.h\"
CONTIKI_PROJECT = coap_leds

TARGETDIRS += ../../platform

all: $(CONTIKI_PROJECT)

APPS += er-coap
APPS += rest-engine

CONTIKI = ../../../../contiki
CONTIKI_WITH_IPV6 = 1
include $(CONTIKI)/Makefile.include
