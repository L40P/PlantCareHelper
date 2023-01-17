#include "Button.h"

#include "../Definitions.h"

#include <Arduino.h>

#define BUTTON_PRESSED LOW
#define BUTTON_RELEASED HIGH

Button::Button(const int& pin) : PIN(pin) {
	pinMode(PIN, INPUT_PULLUP);
	
	previousBounceMillis = millis();
	char reading = digitalRead(PIN);
	previousBounceReading = reading;
	state = reading ? State::RELEASED : State::PRESSED;
}

const Button::State& Button::loop() {
	// read
	char reading = digitalRead(PIN);
	
	// if reading changed from previous bounce reading, this is a new bounce
	if(reading != previousBounceReading) {
		previousBounceMillis = millis();
		previousBounceReading = reading;
	}
	// else this is a potentially stable reading
	// if the time since the last bounce is greater than the set threshold for bounces, this is a stable reading
	else if((millis() - previousBounceMillis) > BUTTON_DEBOUNCE_MILLIS) {
		if(state == State::FALLING_EDGE && reading == BUTTON_RELEASED) {
			state = State::RELEASED;
		}
		else if(state == State::RISING_EDGE && reading == BUTTON_PRESSED) {
			state = State::PRESSED;
		}
		else if((state == State::RELEASED || state == State::FALLING_EDGE) && reading == BUTTON_PRESSED) {
			state = State::RISING_EDGE;
		}
		else if((state == State::PRESSED || state == State::RISING_EDGE) && reading == BUTTON_RELEASED) {
			state = State::FALLING_EDGE;
		}
	}
	
	return state;
}

const Button::State& Button::getState() const {
	return state;
}

bool Button::checkState(const State& state) const {
	return this->state == state;
}

bool Button::isReleased() const {
	return state == State::RELEASED;
}

bool Button::isPressed() const {
	return state == State::PRESSED;
}

bool Button::hasRisingEdge() const {
	return state == State::RISING_EDGE;
}

bool Button::hasFallingEdge() const {
	return state == State::FALLING_EDGE;
}

bool Button::hasEdge() const {
	return state == State::RISING_EDGE || state == State::FALLING_EDGE;
}
