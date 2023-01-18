#ifndef __MENUPRESETDISPLAY__
#define __MENUPRESETDISPLAY__

#include "../Menu.h"
#include "../../data/Preset.h"
#include "../../UniversalDHT/UniversalDHT.h"

class MenuPresetDisplay : public Menu {
public:
	MenuPresetDisplay(Preset* preset);
	~MenuPresetDisplay();
	
	virtual void loop(const Button::State& buttonStateUp, const Button::State& buttonStateDown, const Button::State& buttonStateLeft, const Button::State& buttonStateRight, const Button::State& buttonStateConfirm) override;
	
private:
	Preset* preset;
	
	UniversalDHT dht;
	
	unsigned long millisNextSample = 0;
	void sampleSoil(char& moisture);
	void sampleAir(char& temperature, char& humidity);
	void updateDisplay(char& moisture, char& temperature, char& humidity);
};

#endif
