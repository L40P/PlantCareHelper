#include "MenuB.h"

#include "MenuA.h"
#include "../MenuManager.h"
#include "../../io/DisplayManager.h"

MenuB::MenuB() {
	Serial.println(F("constructed B"));
	DisplayManager::output(F("B"));
}

MenuB::~MenuB() {
	Serial.println(F("destructed B"));
}

void MenuB::loop(const Button::State& buttonStateUp, const Button::State& buttonStateDown, const Button::State& buttonStateLeft, const Button::State& buttonStateRight, const Button::State& buttonStateConfirm) {
	if(buttonStateConfirm == Button::State::RISING_EDGE) {
		delete this;
		MenuManager::menu = new MenuA();
	}
}
