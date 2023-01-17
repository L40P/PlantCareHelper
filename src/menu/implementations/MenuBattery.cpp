#include "MenuBattery.h"

// #include "MenuPresetSelection.h"
#include "MenuA.h"
#include "../MenuManager.h"
#include "../../Definitions.h"
// #include "../../data/SettingManager.h"
#include "../../io/DisplayManager.h"

#include <Arduino_AVRSTL.h>
#include <string>

MenuBattery::MenuBattery() {
	DisplayManager::output(F("---------------\x01"), 0, 2);
	DisplayManager::output((char) 0b00000000, 0, 1); // this is needed for the nullbyte custom character to display
	DisplayManager::output(F("\x04               \x05\xba"), 1, 1);
	DisplayManager::output(F("\x04               \x05\xba"), 2, 1);
	DisplayManager::output(F("\x02---------------\x03"), 3, 1);
	
	pinMode(PIN_BATTERY, INPUT);
	
	float voltage = analogRead(PIN_BATTERY);
	// float min = SettingManager::batteryMinimum.get();
	// float max = SettingManager::batteryMaximum.get();
	float min = 0;
	float max = 1023;
	float length = 15;
	
	int n = (voltage - min) * length / (max - min);
	
	std::string bar = std::string(n, (char) 0b11111111);
	DisplayManager::output(bar.c_str(), 1, 2);
	DisplayManager::output(bar.c_str(), 2, 2);
}

MenuBattery::~MenuBattery() {
	
}

void MenuBattery::loop(const Button::State& buttonStateUp, const Button::State& buttonStateDown, const Button::State& buttonStateLeft, const Button::State& buttonStateRight, const Button::State& buttonStateConfirm) {
	if(buttonStateConfirm == Button::State::RISING_EDGE) {
		delete this;
		// menu = new MenuPresetSelection(MenuPresetSelection::ConfirmAction::MENU_DISPLAY);
		MenuManager::menu = new MenuA();
	}
}
