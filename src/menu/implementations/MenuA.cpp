#include "MenuA.h"

#include "MenuB.h"
#include "../MenuManager.h"
#include "../../io/DisplayManager.h"

MenuA::MenuA() {
	Serial.println(F("constructed A"));
	DisplayManager::output(F("A"));
}

MenuA::~MenuA() {
	Serial.println(F("destructed A"));
}

void MenuA::loop(const Button::State& buttonStateUp, const Button::State& buttonStateDown, const Button::State& buttonStateLeft, const Button::State& buttonStateRight, const Button::State& buttonStateConfirm) {
	if(buttonStateConfirm == Button::State::RISING_EDGE) {
		delete this;
		MenuManager::menu = new MenuB();
	}
}
