#ifndef __MENUPRESETSELECTION__
#define __MENUPRESETSELECTION__

#include "../Menu.h"
#include "../../data/Preset.h"

class MenuPresetSelection : public Menu {
public:
	MenuPresetSelection();
	~MenuPresetSelection();
	
	virtual void loop(const Button::State& buttonStateUp, const Button::State& buttonStateDown, const Button::State& buttonStateLeft, const Button::State& buttonStateRight, const Button::State& buttonStateConfirm) override;
	
private:
	Preset* presets[3];
	unsigned int index;
	
	void updateDisplay();
};

#endif
