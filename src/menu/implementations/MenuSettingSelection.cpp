#include "MenuSettingSelection.h"

// #include "MenuPresetEdit.h"
#include "MenuPresetSelection.h"
#include "MenuSettingEdit.h"
#include "../MenuManager.h"
#include "../../data/PresetManager.h"
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
		MenuManager::menu = new MenuPresetSelection(MenuPresetSelection::ConfirmAction::MENU_DISPLAY);
	}
	else if(buttonStateUp == Button::State::RISING_EDGE) {
		if(position > 0) {
			position--;
			updateDisplay();
		}
	}
	else if(buttonStateDown == Button::State::RISING_EDGE) {
		if(position < 7) {
			position++;
			updateDisplay();
		}
	}
	else if(buttonStateConfirm == Button::State::RISING_EDGE) {
		if(position == 0) {
			
			// search for first empty preset slot
			unsigned int i = 0;
			while(PresetManager::readPreset(i)) {
				i++;
			}
			
			// delete this;
			// MenuManager::menu = new MenuPresetEdit(new Preset(), i);
		}
		else if(position == 1) {
			delete this;
			MenuManager::menu = new MenuPresetSelection(MenuPresetSelection::ConfirmAction::MENU_EDIT);
		}
		else if(position == 2) {
			delete this;
			MenuManager::menu = new MenuSettingEdit<int>("Analog Threshold", SettingManager::moistureSampleThreshold);
		}
		else if(position == 3) {
			delete this;
			MenuManager::menu = new MenuSettingEdit<int>("Moisture Minimum", SettingManager::moistureMin);
		}
		else if(position == 4) {
			delete this;
			MenuManager::menu = new MenuSettingEdit<int>("Moisture Maximum", SettingManager::moistureMax);
		}
		else if(position == 5) {
			delete this;
			MenuManager::menu = new MenuSettingEdit<int>("Battery Minimum", SettingManager::batteryMinimum);
		}
		else if(position == 6) {
			delete this;
			MenuManager::menu = new MenuSettingEdit<int>("Battery Maximum", SettingManager::batteryMaximum);
		}
		else if(position == 7) {
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
	if(position == 0) {
		return F("New Preset          ");
	}
	else if(position == 1) {
		return F("Edit Preset         ");
	}
	else if(position == 2) {
		return F("Analog Threshold    ");
	}
	else if(position == 3) {
		return F("Moisture Minimum    ");
	}
	else if(position == 4) {
		return F("Moisture Maximum    ");
	}
	else if(position == 5) {
		return F("Battery Minimum     ");
	}
	else if(position == 6) {
		return F("Battery Maximum     ");
	}
	else if(position == 7) {
		return F("Temperature Offset  ");
	}
	else {
		return F("                    ");
	}
}
