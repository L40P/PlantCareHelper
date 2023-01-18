#ifndef __PRESETMANAGER__
#define __PRESETMANAGER__

#include "Preset.h"

namespace PresetManager {
	void setup();
	
	void sleep();
	void wakeUp();
	
	Preset* readPreset(const unsigned int& index);
	void writePreset(const unsigned int& index, const Preset* preset);
	
	void clearEEPROM();
}

#endif
