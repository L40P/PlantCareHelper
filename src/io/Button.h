#ifndef __BUTTON__
#define __BUTTON__

class Button {
public:
	Button() = delete;
	Button(int pin);
	Button(int pin, bool pullup);
	
	enum class State {
		RELEASED,
		PRESSED,
		RISING_EDGE,
		FALLING_EDGE,
	};
	
	unsigned long debounceMillis = 50;
	State loop();
	
	State getState();
	bool checkState(State state);
	
	bool isReleased();
	bool isPressed();
	bool hasRisingEdge();
	bool hasFallingEdge();
	bool hasEdge();
	
private:
	const int PIN;
	const int READING_RELEASED;
	const int READING_PRESSED;
	
	unsigned long previousBounceMillis;
	
	int previousBounceReading;
	int previousReading;
	int currentReading;
	
	State state = State::RELEASED;
	void updateState();
};

#endif
