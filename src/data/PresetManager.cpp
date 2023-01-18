#include "PresetManager.h"

#include "../Definitions.h"

#define MAX_INDEX ((EEPROM_SIZE / PRESET_SIZE) - 1)

#define INSTRUCTION_READ (unsigned char) 0b00000011
#define INSTRUCTION_WRITE (unsigned char) 0b00000010
#define INSTRUCTION_WRITE_ENABLE (unsigned char) 0b00000110
#define INSTRUCTION_WRITE_DISABLE (unsigned char) 0b00000100
#define INSTRUCTION_READ_STATUS_REGISTER (unsigned char) 0b00000101
#define INSTRUCTION_WRITE_STATUS_REGISTER (unsigned char) 0b00000001
#define INSTRUCTION_PAGE_ERASE (unsigned char) 0b01000010
#define INSTRUCTION_SECTOR_ERASE (unsigned char) 0b11011000
#define INSTRUCTION_CHIP_ERASE (unsigned char) 0b11000111
#define INSTRUCTION_RELEASE_DEEP_POWER_DOWN_READ_ELECTRONIC_SIGNATURE (unsigned char) 0b10101011
#define INSTRUCTION_DEEP_POWER_DOWN (unsigned char) 0b10111001

namespace {
	void select() {
		digitalWrite(PIN_EEPROM_CS, LOW);
	}
	
	void deselect() {
		digitalWrite(PIN_EEPROM_CS, HIGH);
	}
	
	void sendByte(const unsigned char& byte) {
		shiftOut(PIN_EEPROM_SI, PIN_EEPROM_SCK, MSBFIRST, byte);
	}
	
	unsigned int indexToAddress(const unsigned int& index) {
		unsigned int address = index * PRESET_SIZE;
		return address;
	}
	
	void sendAddress(const unsigned int& address) {
		sendByte((address >> 8) & 0b11111111); // MSB
		sendByte((address >> 0) & 0b11111111); // LSB
	}
	
	unsigned char receiveByte() {
		return shiftIn(PIN_EEPROM_SO, PIN_EEPROM_SCK, MSBFIRST);
	}
	
	unsigned char* receiveBytes(const unsigned int& n) {
		unsigned char* bytes = new unsigned char[n] {1};
		
		for(unsigned int i = 0; i < n; i++) {
			bytes[i] = receiveByte();
		}
		
		return bytes;
	}
	
	unsigned char readStatusRegister() {
		select();
		
		sendByte(INSTRUCTION_READ_STATUS_REGISTER);
		
		unsigned char statusRegister = receiveByte();
		
		deselect();
		
		return statusRegister;
	}
	
	bool isWriteInProcess() {
		return readStatusRegister() & 0b00000001;
	}
	
	void waitOnWrite() {
		while(isWriteInProcess()) ;
	}
	
	unsigned char* readBytes(const unsigned int& address, const unsigned int& n) {
		waitOnWrite();
		
		select();
		
		sendByte(INSTRUCTION_READ);
		sendAddress(address);
		
		unsigned char* bytes = receiveBytes(n);
		
		deselect();
		
		return bytes;
	}
	
	void writeBytes(const unsigned int& address, const unsigned char* bytes, const unsigned int& n) {
		unsigned int i = 0;
		while(i < n) {
			waitOnWrite();
			
			select();
			
			sendByte(INSTRUCTION_WRITE_ENABLE);
			
			deselect();
			
			select();
			
			sendByte(INSTRUCTION_WRITE);
			sendAddress(address + i);
			
			do {
				sendByte(bytes[i]);
				
				i++;
			} while(i < n && (address + i) % EEPROM_PAGE_SIZE != 0);
			
			deselect();
		}
	}
}

void PresetManager::setup() {
	pinMode(PIN_EEPROM_CS, OUTPUT);
	pinMode(PIN_EEPROM_SCK, OUTPUT);
	pinMode(PIN_EEPROM_SI, OUTPUT);
	pinMode(PIN_EEPROM_SO, INPUT);
	
	digitalWrite(PIN_EEPROM_CS, HIGH);
	digitalWrite(PIN_EEPROM_SCK, LOW);
	digitalWrite(PIN_EEPROM_SI, LOW);
	
	Serial.println(F("set up PresetManager"));
	
	wakeUp();
}

void PresetManager::sleep() {
	waitOnWrite();
	
	select();
	
	sendByte(INSTRUCTION_DEEP_POWER_DOWN);
	
	deselect();
	
	Serial.println(F("PresetManager sleeping"));
}

void PresetManager::wakeUp() {
	select();
	
	sendByte(INSTRUCTION_RELEASE_DEEP_POWER_DOWN_READ_ELECTRONIC_SIGNATURE);
	
	deselect();
	
	Serial.println(F("woke up PresetManager"));
}

Preset* PresetManager::readPreset(const unsigned int& index) {
	if(index < 0 || index > MAX_INDEX) {
		return nullptr;
	}
	
	unsigned char* bytes = readBytes(indexToAddress(index), PRESET_SIZE);
	Preset* preset = Preset::fromBytes(bytes);
	delete[] bytes;
	return preset;
}

void PresetManager::writePreset(const unsigned int& index, const Preset* preset) {
	if(index < 0 || index > MAX_INDEX) {
		return;
	}
	
	unsigned char* bytes = Preset::toBytes(preset);
	writeBytes(indexToAddress(index), bytes, PRESET_SIZE);
	delete[] bytes;
}

void PresetManager::clearEEPROM() {
	Serial.println(F("Clearing EEPROM"));
	
	unsigned char bytes[EEPROM_PAGE_SIZE] = {};
	
	for(unsigned int i = 0; i * EEPROM_PAGE_SIZE < EEPROM_SIZE; i++) {
		writeBytes(i * EEPROM_PAGE_SIZE, &bytes[0], EEPROM_PAGE_SIZE);
		
		Serial.print(F("Page "));
		Serial.print(i + 1);
		Serial.println(F(" cleared"));
	}
}
