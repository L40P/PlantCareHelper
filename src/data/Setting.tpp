
#include <Arduino.h>
#include <EEPROM.h>

template <typename T>
Setting<T>::Setting(const int& address, const T& min, const T& max) : ADDRESS(address), MIN(min), MAX(max) {
	load();
}

template <typename T>
void Setting<T>::load() {
	unsigned char bytes[sizeof(T)];
	
	for(unsigned int i = 0; i < sizeof(T); i++) {
		bytes[i] = EEPROM.read(ADDRESS + i);
	}
	
	set(*(T*) &bytes);
}

template <typename T>
void Setting<T>::save() const {
	unsigned char* bytes = (unsigned char*) &value;
	
	for(unsigned int i = 0; i < sizeof(T); i++) {
		EEPROM.update(ADDRESS + i, bytes[i]);
	}
}

template <typename T>
const T& Setting<T>::get() const {
	return value;
}

template <typename T>
void Setting<T>::set(const T& value) {
	if(value < MIN) {
		this->value = MIN;
	}
	else if(value > MAX) {
		this->value = MAX;
	}
	else {
		this->value = value;
	}
}

template <typename T>
void Setting<T>::increment() {
	set(value + 1);
}

template <typename T>
void Setting<T>::decrement() {
	set(value - 1);
}
