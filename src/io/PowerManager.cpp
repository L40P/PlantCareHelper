#include "PowerManager.h"

#include "DisplayManager.h"
#include "../Definitions.h"
#include "../data/PresetManager.h"
#include "../menu/MenuManager.h"

#include <Arduino.h>
#include <avr/power.h>
#include <avr/sleep.h>

namespace {
	unsigned long millisSleep;
	
	void wakeUp() {
		// detach interrupt because we only need it for waking up
		detachInterrupt(digitalPinToInterrupt(PIN_BUTTON_CONFIRM));
	}
	
	void sleep() {
		digitalWrite(PIN_LED_STATUS, LOW);
		
		MenuManager::sleep();
		DisplayManager::sleep();
		PresetManager::sleep();
		
		Serial.println(F("PowerManager sleeping"));
		
		Serial.flush(); // let serial finish transmission
		
		attachInterrupt(digitalPinToInterrupt(PIN_BUTTON_CONFIRM), wakeUp, LOW); // attach interrupt to wake up
		set_sleep_mode(SLEEP_MODE_PWR_DOWN); // set sleep mode to power down
		
		// enable sleep and reduce power consumption by turning off components that are still active
		sleep_enable();
		power_adc_disable();
		power_timer0_disable();
		power_twi_disable();
		power_usart0_disable();
		sleep_cpu();
		
		// after waking up, disable sleep and turn needed components back on
		sleep_disable();
		power_adc_enable(); // needed for soil sensors
		power_timer0_enable(); // needed for system timing functions (millis(), delay(), ...)
		power_twi_enable(); // needed for driving the display
		power_usart0_enable(); // needed for serial communication
		
		PresetManager::wakeUp();
		DisplayManager::wakeUp();
		MenuManager::wakeUp();
		
		Serial.println(F("woke up PowerManager"));
		digitalWrite(PIN_LED_STATUS, HIGH);
		
		PowerManager::extend();
	}
}

void PowerManager::setup() {
	pinMode(PIN_BUTTON_CONFIRM, INPUT_PULLUP);
	
	pinMode(PIN_LED_STATUS, OUTPUT);
	digitalWrite(PIN_LED_STATUS, HIGH);
	
	// we dont need spi, timer1 and timer2
	power_spi_disable();
	power_timer1_disable();
	power_timer2_disable();
	
	extend();
	
	Serial.println(F("set up PowerManager"));
}

void PowerManager::loop() {
	if(millis() >= millisSleep) {
		sleep();
	}
}

void PowerManager::extend() {
	millisSleep = millis() + SLEEP_MILLIS_TIMEOUT;
}
