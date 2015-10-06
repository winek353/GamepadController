#include "DolphinShortcuts.hpp"
#include <iostream>
using namespace std;
#include "Logger.hpp"
#include <cstdlib>

DolphinShortcuts::DolphinShortcuts(ISystemController* systemController)
{
    this->systemController = systemController;
}

void DolphinShortcuts::handleButton(JoypadButton button, PressedOrReleased pressedOrReleased, bool isLT_belowThreshold)
{
	  if(button == BUTTON_A)
	  {
	  if(pressedOrReleased == PRESSED)
		  systemController->pressKey(28);
	  else
		  systemController->releaseKey(28);
	  }
	  if(button == BUTTON_B)
	  {
	  if(pressedOrReleased == PRESSED)
		  systemController->pressKey(14);
	  else
		  systemController->releaseKey(14);
	  }
	  if(button ==  BUTTON_LEFT)
	  {
	  if(pressedOrReleased == PRESSED)
		  systemController->pressKey(105);
	  else
		  systemController->releaseKey(105);
	  }
	  if(button ==  BUTTON_RIGHT)
	  {
	  if(pressedOrReleased == PRESSED)
		  systemController->pressKey(106);
	  else
		  systemController->releaseKey(106);
	  }
	  if(button ==  BUTTON_UP)
	  {
	  if(pressedOrReleased == PRESSED)
		  systemController->pressKey(103);
	  else
		  systemController->releaseKey(103);
	  }
	  if(button ==  BUTTON_DOWN)
	  {
	  if(pressedOrReleased == PRESSED)
		  systemController->pressKey(108);
	  else
		  systemController->releaseKey(108);
	  }
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
