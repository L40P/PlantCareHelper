#include "Preset.h"

Preset::Preset(const char* name, const char& humidityMin, const char& humidityMax, const char& moistureMin, const char& moistureMax) : name(DISPLAY_COLUMNS, ' '), humidityMin(humidityMin), humidityMax(humidityMax), moistureMin(moistureMin), moistureMax(moistureMax) {
	for(unsigned int i = 0; i < DISPLAY_COLUMNS && name[i] != '\0'; i++) {
		this->name[i] = name[i];
	}
}

Preset::Preset() : name(DISPLAY_COLUMNS, ' '), humidityMin(PRESET_HUMIDITY_MIN), humidityMax(PRESET_HUMIDITY_MAX), moistureMin(PRESET_MOISTURE_MIN), moistureMax(PRESET_MOISTURE_MAX) {
	
}

Preset* Preset::fromBytes(const unsigned char* bytes) {
	if(bytes[0] == 0) {
		return nullptr;
	}
	
	Preset* preset = new Preset();
	
	unsigned int i = 0;
	
	// name humidityMin humidityMax moistureMin moistureMax
	while(i < DISPLAY_COLUMNS) {
		preset->name[i] = (char) bytes[i];
		i++;
	}
	preset->humidityMin = bytes[i++];
	preset->humidityMax = bytes[i++];
	preset->moistureMin = bytes[i++];
	preset->moistureMax = bytes[i++];
	
	return preset;
}

unsigned char* Preset::toBytes(const Preset* preset) {
	if(!preset) {
		return new unsigned char[PRESET_SIZE];
	}
	
	unsigned char* bytes = new unsigned char[PRESET_SIZE];
	
	unsigned int i = 0;
	
	while(i < DISPLAY_COLUMNS) {
		bytes[i] = (unsigned char) preset->name[i];
		i++;
	}
	bytes[i++] = preset->humidityMin;
	bytes[i++] = preset->humidityMax;
	bytes[i++] = preset->moistureMin;
	bytes[i++] = preset->moistureMax;
	
	return bytes;
}
