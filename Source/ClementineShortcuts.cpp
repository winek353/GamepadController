#include "ClementineShortcuts.hpp"
#include <iostream>
using namespace std;
#include "Logger.hpp"
#include <cstdlib>

string ClementineShortcuts::getApplication()
{
    return "clementine";
}
void ClementineShortcuts::pressCtrlPlusKey(int key)
{
    systemController->pressKey(29);
    systemController->pressKey(key);
    systemController->releaseKey(key);
    systemController->releaseKey(29);
}
void ClementineShortcuts::pressCtrlPlusShiftPlusKey(int key)
{
   systemController->pressKey(42);
   pressCtrlPlusKey(key);
   systemController->releaseKey(42);
}
void ClementineShortcuts::handleButton(JoypadButton button, PressedOrReleased pressedOrReleased, bool isLT_pressed)
{
  if (pressedOrReleased==PRESSED)
  {
    switch (button)
    {
      case BUTTON_DOWN:
      systemController->pressKey(108);
      systemController->releaseKey(108);
      break;
      case BUTTON_UP:
      systemController->pressKey(103);
      systemController->releaseKey(103);
      break;
      case BUTTON_RIGHT:
      pressCtrlPlusKey(15);
      break;
      case BUTTON_LEFT:
      pressCtrlPlusShiftPlusKey(15);
      break;
      case BUTTON_X:
      systemController->pressKey(28);
      systemController->releaseKey(28);
      break;
    }
  }
}
void ClementineShortcuts::handleAxis(JoypadAxis, int, bool isLT_belowThreshold)
{
  
}
void ClementineShortcuts::handleTime()
{
  
}
ClementineShortcuts::ClementineShortcuts(ISystemController* systemController)
{
    this->systemController = systemController;
}