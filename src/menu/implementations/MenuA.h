#ifndef __MENUA__
#define __MENUA__

#include "../Menu.h"

class MenuA : public Menu {
public:
	MenuA();
	~MenuA();
	
	virtual void loop(const Button::State& buttonStateUp, const Button::State& buttonStateDown, const Button::State& buttonStateLeft, const Button::State& buttonStateRight, const Button::State& buttonStateConfirm) override;
	
private:
	
};

#endif
