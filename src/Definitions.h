#ifndef __DEFINITIONS__
#define __DEFINITIONS__

#include <Arduino.h>
#include <MemoryUsage.h>

#define _printRAM {MEMORY_PRINT_FREERAM;Serial.flush();}
#define _print(s) {Serial.print(F(s));Serial.flush();}
#define _println(s) {Serial.println(F(s));Serial.flush();}



// environment
#define EEPROM_SIZE				65536
#define EEPROM_PAGE_SIZE		128
#define DISPLAY_ADDRESS			0x27
#define DISPLAY_ROWS			4
#define DISPLAY_COLUMNS			20
#define SLEEP_MILLIS_TIMEOUT	30UL * 1000UL // 30s
#define SERIAL_BAUD_RATE		115200
#define BUTTON_DEBOUNCE_MILLIS	50

// analog
#define PIN_SOIL				14
#define PIN_LOW					15
#define PIN_HIGH				16
#define PIN_BATTERY				17

// interrupt
#define PIN_BUTTON_CONFIRM		3

// digital
#define PIN_DHT					2

#define PIN_LED_STATUS 			13

#define PIN_BUTTON_UP			4
#define PIN_BUTTON_DOWN			6
#define PIN_BUTTON_LEFT			7
#define PIN_BUTTON_RIGHT		5

#define PIN_EEPROM_CS			8
#define PIN_EEPROM_SCK			9
#define PIN_EEPROM_SI			10
#define PIN_EEPROM_SO			11



#endif
