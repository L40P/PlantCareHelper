
#include "data/PresetManager.h"
#include "io/DisplayManager.h"
#include "io/PowerManager.h"
#include "io/SerialManager.h"
#include "menu/MenuManager.h"

void setup() {
	SerialManager::setup();
	
	DisplayManager::setup();
	
	PresetManager::setup();
	
	MenuManager::setup();
	
	PowerManager::setup();
}

void loop() {
	SerialManager::loop();
	
	MenuManager::loop();
	
	PowerManager::loop();
}
