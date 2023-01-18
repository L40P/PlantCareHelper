#ifndef __SETTING__
#define __SETTING__

template <typename T>
class Setting {
public:
	Setting(const int& address, const T& min, const T& max);
	
	void load();
	void save() const;
	
	const T& get() const;
	void set(const T& value);
	
	void increment();
	void decrement();
	
private:
	const int ADDRESS;
	const T& MIN;
	const T& MAX;
	
	T value;
};

#include "Setting.tpp"

#endif
