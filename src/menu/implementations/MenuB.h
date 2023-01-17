#ifndef __MENUB__
#define __MENUB__

#include "../Menu.h"

class MenuB : public Menu {
public:
	MenuB();
	~MenuB();
	
	virtual void loop(const Button::State& buttonStateUp, const Button::State& buttonStateDown, const Button::State& buttonStateLeft, const Button::State& buttonStateRight, const Button::State& buttonStateConfirm) override;
	
private:
	
};

#endif
