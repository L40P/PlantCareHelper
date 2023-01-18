#include "MenuPresetSelection.h"

#include "MenuPresetDisplay.h"
#include "MenuSettingSelection.h"
#include "../MenuManager.h"
#include "../../io/DisplayManager.h"
#include "../../data/PresetManager.h"

MenuPresetSelection::MenuPresetSelection() {
	index = 0;
	
	presets[0] = PresetManager::readPreset(index - 1);
	presets[1] = PresetManager::readPreset(index);
	presets[2] = PresetManager::readPreset(index + 1);
	
	DisplayManager::output(F(" <    Presets     > "), 0);
	
	if(presets[1]) {
		DisplayManager::setCursor(2, 0);
		DisplayManager::blinking(true);
		
		updateDisplay();
	}
	else {
		DisplayManager::output(F("  No Presets found  "), 2);
	}
}

MenuPresetSelection::~MenuPresetSelection() {
	delete presets[0];
	delete presets[1];
	delete presets[2];
	
	DisplayManager::blinking(false);
	DisplayManager::setCursor(0, 0);
}

void MenuPresetSelection::loop(const Button::State& buttonStateUp, const Button::State& buttonStateDown, const Button::State& buttonStateLeft, const Button::State& buttonStateRight, const Button::State& buttonStateConfirm) {
	if(buttonStateLeft == Button::State::RISING_EDGE || buttonStateRight == Button::State::RISING_EDGE) {
		delete this;
		MenuManager::menu = new MenuSettingSelection();
	}
	else if(buttonStateUp == Button::State::RISING_EDGE) {
		if(presets[0]) {
			index--;
			
			delete presets[2];
			presets[2] = presets[1];
			presets[1] = presets[0];
			presets[0] = PresetManager::readPreset(index - 1);
			
			updateDisplay();
		}
	}
	else if(buttonStateDown == Button::State::RISING_EDGE) {
		if(presets[2]) {
			index++;
			
			delete presets[0];
			presets[0] = presets[1];
			presets[1] = presets[2];
			presets[2] = PresetManager::readPreset(index + 1);
			
			updateDisplay();
		}
	}
	else if(buttonStateConfirm == Button::State::RISING_EDGE) {
		if(presets[1]) {
			Preset* p = new Preset(*presets[1]);
			delete this;
			MenuManager::menu = new MenuPresetDisplay(p);
		}
	}
}

void MenuPresetSelection::updateDisplay(){
	for(int i = 0; i < 3; i++) {
		if(presets[i]) {
			DisplayManager::output(presets[i]->name.c_str(), i+1);
		}
		else {
			DisplayManager::output(F("                    "), i+1);
		}
	}
}
