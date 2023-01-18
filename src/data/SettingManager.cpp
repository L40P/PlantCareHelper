#include "SettingManager.h"

namespace {
	const int ADC_MIN = 0;
	const int ADC_MAX = 1023;
	const char OFFSET_MIN = -10;
	const char OFFSET_MAX = 10;
}

Setting<int> SettingManager::moistureSampleThreshold(0, ADC_MIN, ADC_MAX);
Setting<int> SettingManager::moistureMin(20, ADC_MIN, ADC_MAX);
Setting<int> SettingManager::moistureMax(40, ADC_MIN, ADC_MAX);
Setting<int> SettingManager::batteryMinimum(60, ADC_MIN, ADC_MAX);
Setting<int> SettingManager::batteryMaximum(80, ADC_MIN, ADC_MAX);
Setting<char> SettingManager::temperatureOffset(100, OFFSET_MIN, OFFSET_MAX);
