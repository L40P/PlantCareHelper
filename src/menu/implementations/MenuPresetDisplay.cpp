#include "MenuPresetDisplay.h"

#include "MenuPresetSelection.h"
#include "../MenuManager.h"
#include "../../Definitions.h"
#include "../../data/SettingManager.h"
#include "../../io/DisplayManager.h"
#include "../../io/StringHelper.h"

#define ERROR_VALUE -1

MenuPresetDisplay::MenuPresetDisplay(Preset* preset) : dht(PIN_DHT) {
	this->preset = preset;
	
	DisplayManager::output(preset->name.c_str(), 0);
	
	// moisture unit and preset moisture values
	DisplayManager::output(F("       \x07       ^    "), 1);
	DisplayManager::output(StringHelper::padFront(StringHelper::toString(preset->moistureMin), ' ', 3).c_str(), 1, 8);
	DisplayManager::output(StringHelper::padFront(StringHelper::toString(preset->moistureMax),' ', 3).c_str(), 1, 16);
	
	// humidity unit and preset humidity values
	DisplayManager::output(F("   %   \x07   %   ^   %"), 2);
	DisplayManager::output(StringHelper::padFront(StringHelper::toString(preset->humidityMin), ' ', 3).c_str(), 2, 8);
	DisplayManager::output(StringHelper::padFront(StringHelper::toString(preset->humidityMax), ' ', 3).c_str(), 2, 16);
	
	// temperature unit
	DisplayManager::output(0b11011111, 3, 2);
	DisplayManager::output('C', 3, 3);
	
	pinMode(PIN_LOW, INPUT);
	digitalWrite(PIN_LOW, LOW);
	
	pinMode(PIN_HIGH, INPUT);
	digitalWrite(PIN_HIGH, HIGH);
	
	pinMode(PIN_SOIL, INPUT);
}

MenuPresetDisplay::~MenuPresetDisplay() {
	delete preset;
}

void MenuPresetDisplay::loop(const Button::State& buttonStateUp, const Button::State& buttonStateDown, const Button::State& buttonStateLeft, const Button::State& buttonStateRight, const Button::State& buttonStateConfirm) {
	if(buttonStateConfirm == Button::State::RISING_EDGE) {
		delete this;
		MenuManager::menu = new MenuPresetSelection();
	}
	else if(millis() > millisNextSample) {
		char moisture;
		char temperature;
		char humidity;
		
		sampleSoil(moisture);
		sampleAir(temperature, humidity);
		
		updateDisplay(moisture, temperature, humidity);
		
		millisNextSample = millis() + 1000;
	}
}

void MenuPresetDisplay::sampleSoil(char& moisture) {
	analogRead(PIN_LOW);
	int sample1 = analogRead(PIN_SOIL);
	analogRead(PIN_HIGH);
	int sample2 = analogRead(PIN_SOIL);
	
	if(abs(sample2 - sample1) > SettingManager::moistureSampleThreshold.get()) {
		Serial.println(F("failed to sample soil"));
		moisture = ERROR_VALUE;
	}
	else {
		float sample = sample2;
		float min = SettingManager::moistureMin.get();
		float max = SettingManager::moistureMax.get();
		float scale = 10.0f;
		moisture = (char) ((sample - min) / (max - min) * scale);
	}
}

void MenuPresetDisplay::sampleAir(char& temperature, char& humidity) {
	float T;
	float H;
	
	UniversalDHT::Response response = dht.read(&H, &T);
	
	if(response.error) {
		Serial.println(F("failed to sample air"));
		temperature = ERROR_VALUE;
		humidity = ERROR_VALUE;
	}
	else {
		temperature = (char) T + SettingManager::temperatureOffset.get();
		humidity = (char) H;
	}
}

void MenuPresetDisplay::updateDisplay(char& moisture, char& temperature, char& humidity) {
	if(moisture == ERROR_VALUE) {
		DisplayManager::output(F("   "), 1, 0);
	}
	else {
		DisplayManager::output(StringHelper::padFront(StringHelper::toString(moisture), ' ', 3).c_str(), 1, 0);
	}
	
	if(temperature == ERROR_VALUE) {
		DisplayManager::output(F("  "), 3, 0);
	}
	else {
		DisplayManager::output(StringHelper::padFront(StringHelper::toString(temperature), ' ', 2).c_str(), 3, 0);
	}
	
	if(humidity == ERROR_VALUE) {
		DisplayManager::output(F("   "), 2, 0);
	}
	else {
		DisplayManager::output(StringHelper::padFront(StringHelper::toString(humidity), ' ', 3).c_str(), 2, 0);
	}
	
	if(moisture == ERROR_VALUE || humidity == ERROR_VALUE) {
		DisplayManager::output(F(" VALUES MISSING"), 3, 5);
	}
	else {
		if(moisture < preset->moistureMin) {
			DisplayManager::output(F("        TOO DRY"), 3, 5);
		}
		else if(moisture > preset->moistureMax) {
			DisplayManager::output(F("        TOO WET"), 3, 5);
		}
		else if(humidity < preset->humidityMin) {
			DisplayManager::output(F("       TOO ARID"), 3, 5);
		}
		else if(humidity > preset->humidityMax) {
			DisplayManager::output(F("      TOO HUMID"), 3, 5);
		}
		else {
			DisplayManager::output(F("           OKAY"), 3, 5);
		}
	}
}
