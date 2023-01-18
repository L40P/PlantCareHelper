#include "Button.h"

#include <Arduino.h>

Button::Button(int pin) : Button(pin, true) {
	
}

Button::Button(int pin, bool pullup) : PIN(pin), READING_RELEASED(pullup ? HIGH : LOW), READING_PRESSED(pullup ? LOW : HIGH) {
	pinMode(PIN, pullup ? INPUT_PULLUP : INPUT);
	digitalWrite(PIN, READING_RELEASED);
	
	previousBounceReading = READING_RELEASED;
	previousReading = READING_RELEASED;
	currentReading = READING_RELEASED;
	
	previousBounceMillis = millis();
}

Button::State Button::loop() {
	// save previous reading
	previousReading = currentReading;
	
	// read
	int reading = digitalRead(PIN);
	
	// if reading changed from previous bounce reading, this is a new bounce
	if(reading != previousBounceReading) {
		previousBounceMillis = millis();
		previousBounceReading = reading;
	}
	// else this is a potentially stable reading
	// if the time since the last bounce is greater than the set threshold for bounces, this is a stable reading
	else if( (millis() - previousBounceMillis) > debounceMillis ) {
		currentReading = reading;
	}
	
	updateState();
	return state;
}

Button::State Button::getState() {
	return state;
}

bool Button::checkState(State state) {
	return getState() == state;
}

void Button::updateState() {
	if(previousReading == READING_RELEASED && currentReading == READING_RELEASED) {
		state = State::RELEASED;
	}
	else if(previousReading == READING_PRESSED && currentReading == READING_PRESSED) {
		state = State::PRESSED;
	}
	else if(previousReading == READING_RELEASED && currentReading == READING_PRESSED) {
		state = State::RISING_EDGE;
	}
	else if(previousReading == READING_PRESSED && currentReading == READING_RELEASED) {
		state = State::FALLING_EDGE;
	}
}

bool Button::isReleased() {
	return checkState(State::RELEASED);
}

bool Button::isPressed() {
	return checkState(State::PRESSED);
}

bool Button::hasRisingEdge() {
	return checkState(State::RISING_EDGE);
}

bool Button::hasFallingEdge() {
	return checkState(State::FALLING_EDGE);
}

bool Button::hasEdge() {
	return hasRisingEdge() || hasFallingEdge();
}
