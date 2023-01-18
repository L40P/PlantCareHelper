#ifndef __PRESET__
#define __PRESET__

#include "../Definitions.h"

#include <Arduino_AVRSTL.h>
#include <string>

#define PRESET_SIZE (DISPLAY_COLUMNS * sizeof(char) + 4 * sizeof(char))
#define PRESET_HUMIDITY_MIN 0
#define PRESET_HUMIDITY_MAX 100
#define PRESET_MOISTURE_MIN 1
#define PRESET_MOISTURE_MAX 10

class Preset {
public:
	Preset();
	Preset(const char* name, const char& humidityMin, const char& humidityMax, const char& moistureMin, const char& moistureMax);
	
	static Preset* fromBytes(const unsigned char* bytes);
	static unsigned char* toBytes(const Preset* preset);
	static const std::string toString(const Preset* preset);
	
	std::string name;
	char humidityMin;
	char humidityMax;
	char moistureMin;
	char moistureMax;
};

#endif
