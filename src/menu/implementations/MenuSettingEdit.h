#ifndef __MENUSETTINGEDIT__
#define __MENUSETTINGEDIT__

#include "../Menu.h"
#include "../../data/Setting.h"

template <typename T>
class MenuSettingEdit : public Menu {
public:
	MenuSettingEdit(const char* title, Setting<T>& setting);
	~MenuSettingEdit();
	
	virtual void loop(const Button::State& buttonStateUp, const Button::State& buttonStateDown, const Button::State& buttonStateLeft, const Button::State& buttonStateRight, const Button::State& buttonStateConfirm) override;
	
private:
	Setting<T>& setting;
	
	bool save;
	
	void updateDisplay();
};

#include "MenuSettingEdit.tpp"

#endif
