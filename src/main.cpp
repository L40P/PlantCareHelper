
#include "Definitions.h"
#include "data/PresetManager.h"
#include "io/DisplayManager.h"
#include "io/PowerManager.h"
#include "menu/MenuManager.h"

void setup() {
	Serial.begin(SERIAL_BAUD_RATE);
	
	PresetManager::setup();
	_println("preset")
	
	DisplayManager::setup();
	_println("display")
	
	PowerManager::setup();
	_println("power")
	
	MenuManager::setup();
	_println("menu")
	
	// Preset* p = new Preset("asdf               ", 0, 10, 0, 10);
	// PresetManager::writePreset(0, p);
	// delete p;
	// p = nullptr;
	// PresetManager::writePreset(1, p);
	// delete p;
}

void loop() {
	PowerManager::loop();
	
	MenuManager::loop();
	
	// _printRAM
	
	// delay(500);
}
