#ifndef __MENUSETTINGSELECTION__
#define __MENUSETTINGSELECTION__

#include "../Menu.h"

#include <Arduino.h>

class MenuSettingSelection : public Menu {
public:
	MenuSettingSelection();
	~MenuSettingSelection();
	
	virtual void loop(const Button::State& buttonStateUp, const Button::State& buttonStateDown, const Button::State& buttonStateLeft, const Button::State& buttonStateRight, const Button::State& buttonStateConfirm) override;
	
private:
	unsigned int position = 0;
	
	void updateDisplay();
	const __FlashStringHelper* getMenuEntry(unsigned int position);
};

#endif
