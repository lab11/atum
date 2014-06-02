#ifndef RV3049_H_
#define RV3049_H_

// Addresses for the RTC registers
#define RV3049_PAGE_ADDR_CONTROL     0x00
#define RV3049_PAGE_ADDR_CLOCK       0x08
#define RV3049_PAGE_ADDR_ALARM       0x10
#define RV3049_PAGE_ADDR_TIMER       0x18
#define RV3049_PAGE_ADDR_TEMP        0x20
#define RV3049_PAGE_ADDR_EEPROM_USER 0x28
#define RV3049_PAGE_ADDR_EEPROM_CTRL 0x30
#define RV3049_PAGE_ADDR_RAM         0x38

#define RV3049_READ_LEN_TIME 7

#define RV3049_WRITE_LEN_TIME 7

#define RV3049_SET_READ_BIT(command) (0x80 | command)
#define RV3049_SET_WRITE_BIT(command) (0x7F & command)

#define BCD_TO_BINARY(v) ((v & 0x0F) + (((v & 0x10)>>4)*10) + (((v & 0x20)>>5)*20) + (((v & 0x40)>>6)*40))

typedef enum {
  JANUARY   = 1,
  FEBRUARY  = 2,
  MARCH     = 3,
  APRIL     = 4,
  MAY       = 5,
  JUNE      = 6,
  JULY      = 7,
  AUGUST    = 8,
  SEPTEMBER = 9,
  OCTOBER   = 10,
  NOVEMBER  = 11,
  DECEMBER  = 12
} month_e;

typedef enum {
  SUNDAY    = 1,
  MONDAY    = 2,
  TUESDAY   = 3,
  WEDNESDAY = 4,
  THURSDAY  = 5,
  FRIDAY    = 6,
  SATURDAY  = 7
} day_e;

typedef struct {
  uint8_t seconds;
  uint8_t minutes;
  uint8_t hours;
  uint8_t days;
  day_e weekday;
  month_e month;
  uint16_t year;
} rv3049_time_t;

void rv3049_init();
int rv3049_read_time(rv3049_time_t* time);
int rv3049_set_time(rv3049_time_t* time);

#endif