#ifndef __MENUMANAGER__
#define __MENUMANAGER__

#include "Menu.h"

namespace MenuManager {
	void setup();
	void loop();
	
	void sleep();
	void wakeUp();
	
	extern Menu* menu;
}

#endif
