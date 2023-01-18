#include "MenuSettingSelection.h"

#include "MenuPresetSelection.h"
#include "MenuSettingEdit.h"
#include "../MenuManager.h"
#include "../../data/SettingManager.h"
#include "../../io/DisplayManager.h"

MenuSettingSelection::MenuSettingSelection() {
	DisplayManager::output(F(" <    Settings    > "), 0);
	DisplayManager::setCursor(2, 0);
	DisplayManager::blinking(true);
	
	updateDisplay();
}

MenuSettingSelection::~MenuSettingSelection() {
	DisplayManager::blinking(false);
	DisplayManager::setCursor(0, 0);
}

void MenuSettingSelection::loop(const Button::State& buttonStateUp, const Button::State& buttonStateDown, const Button::State& buttonStateLeft, const Button::State& buttonStateRight, const Button::State& buttonStateConfirm) {
	if(buttonStateLeft == Button::State::RISING_EDGE || buttonStateRight == Button::State::RISING_EDGE) {
		delete this;
		MenuManager::menu = new MenuPresetSelection();
	}
	else if(buttonStateUp == Button::State::RISING_EDGE) {
		if(position > 0) {
			position--;
			updateDisplay();
		}
	}
	else if(buttonStateDown == Button::State::RISING_EDGE) {
		if(position < 5) {
			position++;
			updateDisplay();
		}
	}
	else if(buttonStateConfirm == Button::State::RISING_EDGE) {
		unsigned char i = 0;
		
		if(position == i++) {
			delete this;
			MenuManager::menu = new MenuSettingEdit<int>("Analog Threshold", SettingManager::moistureSampleThreshold);
		}
		else if(position == i++) {
			delete this;
			MenuManager::menu = new MenuSettingEdit<int>("Moisture Minimum", SettingManager::moistureMin);
		}
		else if(position == i++) {
			delete this;
			MenuManager::menu = new MenuSettingEdit<int>("Moisture Maximum", SettingManager::moistureMax);
		}
		else if(position == i++) {
			delete this;
			MenuManager::menu = new MenuSettingEdit<int>("Battery Minimum", SettingManager::batteryMinimum);
		}
		else if(position == i++) {
			delete this;
			MenuManager::menu = new MenuSettingEdit<int>("Battery Maximum", SettingManager::batteryMaximum);
		}
		else if(position == i++) {
			delete this;
			MenuManager::menu = new MenuSettingEdit<char>("Temperature Offset", SettingManager::temperatureOffset);
		}
	}
}

void MenuSettingSelection::updateDisplay() {
	DisplayManager::output(getMenuEntry(position - 1), 1);
	DisplayManager::output(getMenuEntry(position), 2);
	DisplayManager::output(getMenuEntry(position + 1), 3);
}

const __FlashStringHelper* MenuSettingSelection::getMenuEntry(unsigned int position) {
	unsigned char i = 0;
	
	if(position == i++) {
		return F("Analog Threshold    ");
	}
	else if(position == i++) {
		return F("Moisture Minimum    ");
	}
	else if(position == i++) {
		return F("Moisture Maximum    ");
	}
	else if(position == i++) {
		return F("Battery Minimum     ");
	}
	else if(position == i++) {
		return F("Battery Maximum     ");
	}
	else if(position == i++) {
		return F("Temperature Offset  ");
	}
	else {
		return F("                    ");
	}
}
