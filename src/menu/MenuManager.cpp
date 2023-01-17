#include "MenuManager.h"

#include "implementations/MenuBattery.h"
#include "../Definitions.h"
#include "../io/Button.h"
#include "../io/DisplayManager.h"
#include "../io/PowerManager.h"

namespace {
	Button buttonUp = Button(PIN_BUTTON_UP);
	Button buttonDown = Button(PIN_BUTTON_DOWN);
	Button buttonLeft = Button(PIN_BUTTON_LEFT);
	Button buttonRight = Button(PIN_BUTTON_RIGHT);
	Button buttonConfirm = Button(PIN_BUTTON_CONFIRM);
}

Menu* MenuManager::menu = nullptr;

void MenuManager::setup() {
	wakeUp();
}

void MenuManager::loop() {
	const Button::State& buttonUpState = buttonUp.loop();
	const Button::State& buttonDownState = buttonDown.loop();
	const Button::State& buttonLeftState = buttonLeft.loop();
	const Button::State& buttonRightState = buttonRight.loop();
	const Button::State& buttonConfirmState = buttonConfirm.loop();
	
	if(buttonUpState == Button::State::RISING_EDGE || buttonDownState == Button::State::RISING_EDGE || buttonLeftState == Button::State::RISING_EDGE || buttonRightState == Button::State::RISING_EDGE || buttonConfirmState == Button::State::RISING_EDGE) {
		PowerManager::extend();
	}
	
	if(menu) {
		menu->loop(buttonUpState, buttonDownState, buttonLeftState, buttonRightState, buttonConfirmState);
	}
}

void MenuManager::sleep() {
	delete menu;
	menu = nullptr;
}

void MenuManager::wakeUp() {
	buttonUp.loop();
	buttonDown.loop();
	buttonLeft.loop();
	buttonRight.loop();
	buttonConfirm.loop();
	
	menu = new MenuBattery();
}
