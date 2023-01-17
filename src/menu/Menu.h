#ifndef __MENU__
#define __MENU__

#include "../io/Button.h"
#include "../io/DisplayManager.h"

class Menu {
public:
	Menu() {}
	virtual ~Menu() {
		DisplayManager::clear();
	}
	
	virtual void loop(const Button::State& buttonStateUp, const Button::State& buttonStateDown, const Button::State& buttonStateLeft, const Button::State& buttonStateRight, const Button::State& buttonStateConfirm) = 0;
};

#endif



/* MENU H TEMPLATE
#ifndef __MENU$__
#define __MENU$__

#include "../Menu.h"

class Menu$ : public Menu {
public:
	Menu$();
	~Menu$();
	
	virtual void loop(const Button::State& buttonStateUp, const Button::State& buttonStateDown, const Button::State& buttonStateLeft, const Button::State& buttonStateRight, const Button::State& buttonStateConfirm) override;
	
private:
	
};

#endif

*/

/* MENU CPP TEMPLATE
#include "Menu$.h"

#include "../MenuManager.h"
#include "../../io/DisplayManager.h"

Menu$::Menu$() {
	
}

Menu$::~Menu$() {
	
}

void Menu$::loop(const Button::State& buttonStateUp, const Button::State& buttonStateDown, const Button::State& buttonStateLeft, const Button::State& buttonStateRight, const Button::State& buttonStateConfirm) {
	
}

*/
