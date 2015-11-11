#include "WormsShortcuts.hpp"

WormsShortcuts::WormsShortcuts(ISystemController* systemController,
                               IConfigStore* configStore,
                               IKeyPresser& keyPresser) :
    ApplicationShortcutsBase(systemController, configStore, keyPresser)
{
}

string WormsShortcuts::getApplication()
{
    return "WormsReloaded.b";
}

void WormsShortcuts::handleButton(JoypadButton button, PressedOrReleased pressedOrReleased, bool isLT_belowThreshold)
{
    
    switch(button)
    {
        case BUTTON_A:
            if(pressedOrReleased == PRESSED)
                keyPresser.pressKey(57);
            else
                keyPresser.releaseKey(57);
            break;
        case BUTTON_X:
            if(pressedOrReleased == PRESSED)
                keyPresser.pressKey(28);
            else
                keyPresser.releaseKey(28);
            break;
        case BUTTON_Y:
            if(pressedOrReleased == PRESSED)
                keyPresser.pressKey(14);
            else
                keyPresser.releaseKey(14);
            break;
    }

    arrowsToArrowsPresser.pressArrow(button, pressedOrReleased);
}

void WormsShortcuts::handleAxis(JoypadAxis axis, int value, bool isLT_belowThreshold)
{
    switch(axis)
    {
        case AXIS_LT:
            if(oldLt < thresholdLtRt && value >= thresholdLtRt)
            {
                sysController->clickMouse(4);
            }
            oldLt = value;
            break;
        case AXIS_RT:
            if(oldRt < thresholdLtRt && value >= thresholdLtRt)
            {
                sysController->clickMouse(5);
            }
            oldRt = value;
            break;
    }
}

void WormsShortcuts::handleTime()
{

}

