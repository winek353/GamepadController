#include "ChromeShortcuts.hpp"
#include "IKeyPresser.hpp"
#include <iostream>
using namespace std;
#include "Logger.hpp"
#include <cstdlib>


ChromeShortcuts::ChromeShortcuts(ISystemController* systemController,
                                 IConfigStore* configStore,
                                 IKeyPresser& keyPresser) :
    ApplicationShortcutsBase(systemController, configStore, keyPresser)
{
}

void ChromeShortcuts::handleButton(JoypadButton button, PressedOrReleased pressedOrReleased, bool isLT_belowThreshold)
{
    if(pressedOrReleased == PRESSED)
        return;

    if(isLT_belowThreshold==false)
    {
        switch(button)
        {
            case BUTTON_A:
                keyPresser.pressCtrlPlusKey(20);
                break;
            case BUTTON_B:
                keyPresser.pressCtrlPlusKey(17);
                break;
            case BUTTON_X:
                keyPresser.pressAndReleaseKey(57);
                break;
            case BUTTON_Y:
                keyPresser.pressAndReleaseKey(87);
                break;
            case BUTTON_LEFT:
                keyPresser.pressCtrlPlusKey(104);
                break;
            case BUTTON_RIGHT:
                keyPresser.pressCtrlPlusKey(109);
                break;
            case BUTTON_UP:
                keyPresser.pressCtrlPlusKey(13);
                break;
            case BUTTON_DOWN:
                keyPresser.pressCtrlPlusKey(12);
                break;
        }
    }
    else
    {
        switch(button)
        {
            case BUTTON_LEFT:
                keyPresser.pressAndReleaseKey(105);
                break;
            case BUTTON_RIGHT:
                keyPresser.pressAndReleaseKey(106);
                break;
        }
    }
}
void ChromeShortcuts::handleAxis(JoypadAxis axis, int value, bool isLT_belowThreshold)
{
    if (axis==AXIS_LEFT_VERTICAL)
      mouseScrooler.setAxisValue(value);
}
void ChromeShortcuts::handleTime() // once a 1/20 s
{
  mouseScrooler.handleTime();
}

string ChromeShortcuts::getApplication()
{
  return "chrome";
}
