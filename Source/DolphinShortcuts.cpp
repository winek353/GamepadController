#include "DolphinShortcuts.hpp"
#include <iostream>
using namespace std;
#include "Logger.hpp"
#include <cstdlib>

DolphinShortcuts::DolphinShortcuts(ISystemController* systemController,
                                   IConfigStore* configStore,
                                   IKeyPresser& keyPresser) :
  ApplicationShortcutsBase(systemController, configStore, keyPresser)
{
}

void DolphinShortcuts::handleButton(JoypadButton button, PressedOrReleased pressedOrReleased, bool isLT_belowThreshold)
{
  if(pressedOrReleased == PRESSED)
  {
      switch(button)
      {
        case BUTTON_A:
          keyPresser.pressAndReleaseKey(28);
          break;
        case BUTTON_B:
          keyPresser.pressAndReleaseKey(14);
          break;
      }
  }

  arrowsToArrowsPresser.pressArrow(button, pressedOrReleased);
}

string DolphinShortcuts::getApplication()
{
  return "dolphin";
}

void DolphinShortcuts::handleAxis(JoypadAxis, int, bool isLT_belowThreshold)
{
  
}

void DolphinShortcuts::handleTime()
{
  
}
