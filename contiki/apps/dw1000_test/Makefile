DEFINES+=PROJECT_CONF_H=\"project-conf.h\"
CONTIKI_PROJECT = dw1000_test

TARGETDIRS += ../../platform

USE_DECAWAVE = 1

all: $(CONTIKI_PROJECT)

#LDFLAGS += --specs=nano.specs -u _printf_float
LDFLAGS += --specs=nano.specs

CONTIKI = ../../../../contiki
include $(CONTIKI)/Makefile.include
