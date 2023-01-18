#include "DisplayManager.h"

#include "../Definitions.h"

#include <LiquidCrystal_I2C.h>

namespace {
	LiquidCrystal_I2C lcd = LiquidCrystal_I2C(DISPLAY_ADDRESS, DISPLAY_COLUMNS, DISPLAY_ROWS);
	
	uint8_t cursorRow = 0;
	uint8_t cursorColumn = 0;
	
	void resetCursor() {
		lcd.setCursor(cursorColumn, cursorRow);
	}
}

void DisplayManager::setup() {
	lcd.init();
	clear();
	lcd.backlight();
	
	// load custom characters
	
	// "\x00" - battery corner top left
	byte customCharacter0[] = {
		0b00000,
		0b00000,
		0b00000,
		0b00111,
		0b00100,
		0b00100,
		0b00100,
		0b00100,
	};
	lcd.createChar((byte) 0, customCharacter0);
	
	// "\x01" - battery corner top right
	byte customCharacter1[] = {
		0b00000,
		0b00000,
		0b00000,
		0b11100,
		0b00100,
		0b00100,
		0b00100,
		0b00100,
	};
	lcd.createChar((byte) 1, customCharacter1);
	
	// "\x02" - battery corner bottom left
	byte customCharacter2[] = {
		0b00100,
		0b00100,
		0b00100,
		0b00111,
		0b00000,
		0b00000,
		0b00000,
		0b00000,
	};
	lcd.createChar((byte) 2, customCharacter2);
	
	// "\x03" - battery corner bottom right
	byte customCharacter3[] = {
		0b00100,
		0b00100,
		0b00100,
		0b11100,
		0b00000,
		0b00000,
		0b00000,
		0b00000,
	};
	lcd.createChar((byte) 3, customCharacter3);
	
	// "\x04" - battery edge left
	byte customCharacter4[] = {
		0b00100,
		0b00100,
		0b00100,
		0b00100,
		0b00100,
		0b00100,
		0b00100,
		0b00100,
	};
	lcd.createChar((byte) 4, customCharacter4);
	
	// "\x05" - battery edge right
	byte customCharacter5[] = {
		0b00100,
		0b00111,
		0b00100,
		0b00100,
		0b00100,
		0b00100,
		0b00111,
		0b00100,
	};
	lcd.createChar((byte) 5, customCharacter5);
	
	// "\x06" - 
	byte customCharacter6[] = {
		0b00000,
		0b00000,
		0b00000,
		0b00000,
		0b00000,
		0b00000,
		0b00000,
		0b00000,
	};
	lcd.createChar((byte) 6, customCharacter6);
	
	// "\x07" - arrow down
	byte customCharacter7[] = {
		0b00000,
		0b00000,
		0b00000,
		0b00000,
		0b10001,
		0b01010,
		0b00100,
		0b00000,
	};
	lcd.createChar((byte) 7, customCharacter7);
	
	Serial.println(F("set up DisplayManager"));
}

void DisplayManager::sleep() {
	lcd.noBacklight();
	clear();
	
	Serial.println(F("DisplayManager sleeping"));
}

void DisplayManager::wakeUp() {
	lcd.backlight();
	
	Serial.println(F("woke up DisplayManager"));
}

void DisplayManager::clear() {
	lcd.clear();
}

void DisplayManager::blinking(const bool& enabled) {
	enabled ? lcd.blink() : lcd.noBlink();
}

void DisplayManager::cursor(const bool& enabled) {
	enabled ? lcd.cursor() : lcd.noCursor();
}

void DisplayManager::setCursor(const uint8_t& row, const uint8_t& column) {
	if(row < 0 || row >= DISPLAY_ROWS || column < 0 || column >= DISPLAY_COLUMNS) {
		return;
	}
	
	cursorRow = row;
	cursorColumn = column;
	
	resetCursor();
}

void DisplayManager::output(const char* string) {
	output(string, 0, 0);
}

void DisplayManager::output(const char* string, const uint8_t& row) {
	output(string, row, 0);
}

void DisplayManager::output(const char* string, const uint8_t& row, const uint8_t& column) {
	lcd.setCursor(column, row);
	lcd.print(string);
	resetCursor();
}

void DisplayManager::output(const __FlashStringHelper* string) {
	output(string, 0, 0);
}

void DisplayManager::output(const __FlashStringHelper* string, const uint8_t& row) {
	output(string, row, 0);
}

void DisplayManager::output(const __FlashStringHelper* string, const uint8_t& row, const uint8_t& column) {
	lcd.setCursor(column, row);
	lcd.print(string);
	resetCursor();
}

void DisplayManager::output(const char& c, const uint8_t& row, const uint8_t& column) {
	lcd.setCursor(column, row);
	lcd.print(c);
	resetCursor();
}
