#ifndef __SETTINGMANAGER__
#define __SETTINGMANAGER__

#include "Setting.h"

namespace SettingManager {
	extern Setting<int> moistureSampleThreshold;
	extern Setting<int> moistureMin;
	extern Setting<int> moistureMax;
	extern Setting<int> batteryMinimum;
	extern Setting<int> batteryMaximum;
	extern Setting<char> temperatureOffset;
}

#endif
