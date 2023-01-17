#ifndef __BUTTON__
#define __BUTTON__

class Button {
public:
	Button(const int& pin);
	
	enum class State : char {
		RELEASED,
		PRESSED,
		RISING_EDGE,
		FALLING_EDGE,
	};
	
	const State& loop();
	const State& getState() const;
	
	bool checkState(const State& state) const;
	bool isReleased() const;
	bool isPressed() const;
	bool hasRisingEdge() const;
	bool hasFallingEdge() const;
	bool hasEdge() const;
	
private:
	const char PIN;
	
	unsigned long previousBounceMillis;
	char previousBounceReading;
	State state;
};

#endif
