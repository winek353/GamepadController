#pragma once
#include "ISystemController.hpp"
#include "JoypadButton.hpp"
#include "PressedOrReleased.hpp"
#include "JoypadAxis.hpp"

class ChromeShortcuts
{
public:
    ChromeShortcuts(ISystemController*);

    void chromeButtons(JoypadButton button, PressedOrReleased pressedOrReleased);
    void chromeAxis(JoypadAxis axis, int value);
    void handleTime();
    void verMovements();
    void horMovements();
private:
    ISystemController* systemController;
    int  frequencyHOR;
    int eventCounterHOR;
    bool moveOrNotHOR;
    int  frequencyVER;
    int eventCounterVER;
    bool moveOrNotVER;
};
