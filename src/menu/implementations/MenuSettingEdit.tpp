
#include "MenuSettingSelection.h"
#include "../MenuManager.h"
#include "../../io/DisplayManager.h"
#include "../../io/StringHelper.h"

template <typename T>
MenuSettingEdit<T>::MenuSettingEdit(const char* title, Setting<T>& setting) : setting(setting) {
	save = false;
	
	DisplayManager::output(StringHelper::padCenter(title, ' ', 20).c_str(), 0);
	DisplayManager::output(F(" <                > "), 1);
	DisplayManager::output(F("Cancel"), 2);
	DisplayManager::output(F("Save"), 3);
	
	DisplayManager::blinking(true);
	
	updateDisplay();
}

template <typename T>
MenuSettingEdit<T>::~MenuSettingEdit() {
	DisplayManager::blinking(false);
	DisplayManager::setCursor(0, 0);
}

template <typename T>
void MenuSettingEdit<T>::loop(const Button::State& buttonStateUp, const Button::State& buttonStateDown, const Button::State& buttonStateLeft, const Button::State& buttonStateRight, const Button::State& buttonStateConfirm) {
	if(buttonStateLeft == Button::State::RISING_EDGE) {
		setting.decrement();
		updateDisplay();
	}
	else if(buttonStateRight == Button::State::RISING_EDGE) {
		setting.increment();
		updateDisplay();
	}
	if(buttonStateUp == Button::State::RISING_EDGE || buttonStateDown == Button::State::RISING_EDGE) {
		save = !save;
		updateDisplay();
	}
	else if(buttonStateConfirm == Button::State::RISING_EDGE) {
		if(save) {
			setting.save();
		}
		else {
			setting.load();
		}
		delete this;
		MenuManager::menu = new MenuSettingSelection();
	}
}

template <typename T>
void MenuSettingEdit<T>::updateDisplay() {
	if(save) {
		DisplayManager::setCursor(3, 0);
	}
	else {
		DisplayManager::setCursor(2, 0);
	}
	
	DisplayManager::output(StringHelper::padCenter(StringHelper::toString(setting.get()), ' ', 16).c_str(), 1, 2);
}
