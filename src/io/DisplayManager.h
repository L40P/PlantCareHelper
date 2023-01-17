#ifndef __DISPLAYMANAGER__
#define __DISPLAYMANAGER__

#include <Arduino.h>

namespace DisplayManager {
	void setup();
	
	void sleep();
	void wakeUp();
	
	void clear();
	void blinking(const bool& enabled);
	void cursor(const bool& enabled);
	void setCursor(const uint8_t& row, const uint8_t& column);
	
	void output(const char* string);
	void output(const char* string, const uint8_t& row);
	void output(const char* string, const uint8_t& row, const uint8_t& column);
	
	void output(const __FlashStringHelper* string);
	void output(const __FlashStringHelper* string, const uint8_t& row);
	void output(const __FlashStringHelper* string, const uint8_t& row, const uint8_t& column);
	
	void output(const char& c, const uint8_t& row, const uint8_t& column);
}

#endif
