#include "SerialManager.h"

#include "PowerManager.h"
#include "StringHelper.h"
#include "../Definitions.h"
#include "../data/Preset.h"
#include "../data/PresetManager.h"

#include <Arduino.h>
#include <Arduino_AVRSTL.h>
#include <string>
#include <vector>

namespace {
	std::string commandBuffer;
	
	void printPreset(Preset* preset) {
		Serial.print(F("Preset("));
		
		if(preset) {
			Serial.print(F("\""));
			Serial.print(preset->name.c_str());
			Serial.print(F("\", "));
			Serial.print(StringHelper::toString(preset->humidityMin).c_str());
			Serial.print(F(", "));
			Serial.print(StringHelper::toString(preset->humidityMax).c_str());
			Serial.print(F(", "));
			Serial.print(StringHelper::toString(preset->moistureMin).c_str());
			Serial.print(F(", "));
			Serial.print(StringHelper::toString(preset->moistureMax).c_str());
		}
		
		Serial.print(F(")"));
	}
	
	void executeCommand(const std::string& command) {
		Serial.print(F("Executing command \""));
		Serial.print(commandBuffer.c_str());
		Serial.println(F("\""));
		
		if(command.empty()) return;
		
		std::vector<std::string> elements = StringHelper::splitIntoElements(command);
		
		if(command == "help") {
			Serial.println(F("\"help\" - this list"));
			Serial.println(F("\"index\" - read preset at index"));
			Serial.println(F("\"index.name.humidityMin.humidityMax.moistureMin.moistureMax\" - write preset at index"));
			Serial.println(F("\"index.\" - delete preset at index"));
			Serial.println(F("\"clearpresets\" - delete all presets"));
		}
		else if(command == "clearpresets") {
			PresetManager::clearEEPROM();
		}
		else if(elements.size() == 1) {
			unsigned int index = StringHelper::toInt(elements[0]);
			
			Preset* p = PresetManager::readPreset(index);
			
			Serial.print(F("Read "));
			printPreset(p);
			Serial.print(F(" from index "));
			Serial.print(index);
			Serial.println();
			
			delete p;
		}
		else if(elements.size() == 6) {
			unsigned int index = StringHelper::toInt(elements[0]);
			
			Preset* p = new Preset(elements[1].c_str(), (char) StringHelper::toInt(elements[2]), (char) StringHelper::toInt(elements[3]), (char) StringHelper::toInt(elements[4]), (char) StringHelper::toInt(elements[5]));
			PresetManager::writePreset(index, p);
			
			Serial.print(F("Wrote "));
			printPreset(p);
			Serial.print(F(" to index "));
			Serial.print(index);
			Serial.println();
			
			delete p;
		}
		else if(elements.size() == 2 && elements[1].empty()) {
			unsigned int index = StringHelper::toInt(elements[0]);
			
			Preset* p = PresetManager::readPreset(index);
			PresetManager::writePreset(index, nullptr);
			
			Serial.print(F("Deleted "));
			printPreset(p);
			Serial.print(F(" at index "));
			Serial.print(index);
			Serial.println();
			
			delete p;
		}
		
		Serial.println(F("Done"));
	}
}

void SerialManager::setup() {
	Serial.begin(SERIAL_BAUD_RATE);
	while(!Serial) ;
	
	Serial.println();
	Serial.println(F("-------------------------------"));
	Serial.println(F("         SERIAL STARTED        "));
	Serial.println(F("\"help\" for available commands"));
	Serial.println(F("-------------------------------"));
	Serial.println();
	
	Serial.println(F("set up SerialManager"));
}

void SerialManager::loop() {
	while(Serial.available()) { // if data was send via serial monitor
		PowerManager::extend();
		
		int byte = Serial.read(); // read the data byte by byte
		
		if(byte >= 32 && byte <= 126) { // ascii printable characters are part of the command
			commandBuffer += byte;
		}
		else if(byte == '\b') { // explicitly handle backspace
			if(!commandBuffer.empty()) {
				commandBuffer.pop_back();
			}
		}
		else if(byte == '\n') { // newline means the command is complete
			executeCommand(commandBuffer);
			commandBuffer = "";
		}
		else {
			
		}
	}
}
