#ifndef __MENUBATTERY__
#define __MENUBATTERY__

#include "../Menu.h"

class MenuBattery : public Menu {
public:
	MenuBattery();
	~MenuBattery();
	
	virtual void loop(const Button::State& buttonStateUp, const Button::State& buttonStateDown, const Button::State& buttonStateLeft, const Button::State& buttonStateRight, const Button::State& buttonStateConfirm) override;
	
private:
	
};

#endif
