#pragma once
#include "ApplicationShortcutsBase.hpp"

class WormsShortcuts : public ApplicationShortcutsBase
{
public:
    WormsShortcuts(ISystemController*,
                   IConfigStore*,
                   IKeyPresser&);

    string getApplication();
    void handleButton(JoypadButton button, PressedOrReleased pressedOrReleased, bool isLT_belowThreshold);
    void handleAxis(JoypadAxis axis, int value, bool isLT_belowThreshold);
    void handleTime();

private:
    int oldLt = 0;
    int oldRt = 0;

    static const int thresholdLtRt = 20000;
};

