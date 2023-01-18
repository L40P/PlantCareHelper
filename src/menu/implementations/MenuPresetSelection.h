#ifndef __MENUPRESETSELECTION__
#define __MENUPRESETSELECTION__

#include "../Menu.h"
#include "../../data/Preset.h"

class MenuPresetSelection : public Menu {
public:
	enum class ConfirmAction : char {
		MENU_DISPLAY,
		MENU_EDIT,
	};
	
	MenuPresetSelection(const ConfirmAction& confirmAction);
	~MenuPresetSelection();
	
	virtual void loop(const Button::State& buttonStateUp, const Button::State& buttonStateDown, const Button::State& buttonStateLeft, const Button::State& buttonStateRight, const Button::State& buttonStateConfirm) override;
	
private:
	const ConfirmAction CONFIRM_ACTION;
	
	Preset* presets[3];
	unsigned int index;
	
	void updateDisplay();
};

#endif
