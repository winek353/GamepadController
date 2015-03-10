#include "JoypadHandler.hpp"
#include <iostream>
#include "Logger.hpp"
#include "IConfigStore.hpp"


using namespace std;

JoypadHandler::JoypadHandler(ISystemController* p_systemController,
                             IConfigStore* p_configStore) :
  systemController(p_systemController),
  configStore(p_configStore),
  chromeShortcuts(p_systemController)
{
	mouseSpeedX = 0;
	mouseSpeedY = 0;
	flag = true;
    isLT_pressed = false;
}
int calculateMouseSpeed (int value,IConfigStore* configStore  )
    {
        if (value >= configStore->getMouseDeadZoneSize())
	  return (value - configStore->getMouseDeadZoneSize()) / configStore->getReversedMouseSpeed();
        else if(value <= -configStore->getMouseDeadZoneSize())
	  return (value + configStore->getMouseDeadZoneSize()) / configStore->getReversedMouseSpeed();
        else return 0;
    }
bool isLT_belowThreshold (int value, IConfigStore* configStore)
    {
        if(value>= configStore->getLtPressedThreshold())
        {
             return true;
        }
        else
        {
            return false;
        }
    }
void JoypadHandler::pressCtrlPlusAltPlusKey(int key)
{
    systemController->pressKey(29);
    systemController->pressKey(56);
    systemController->pressKey(key);
    systemController->releaseKey(key);
    systemController->releaseKey(56);
    systemController->releaseKey(29);
}

void JoypadHandler::handleButton(JoypadButton button, PressedOrReleased pressedOrReleased)
{
  DEBUG << "Button " << button << " was " << pressedOrReleased;
  if(systemController->getApplicationOnTop().compare("steam")!=0)
    {
	    if(systemController->getApplicationOnTop().compare("chrome")==0)
	    {
		chromeShortcuts.chromeButtons(button, pressedOrReleased,isLT_pressed);
	    }
	    if(button==BUTTON_XBOX)
	    {
		if(pressedOrReleased == PRESSED)
		    systemController->runCommand("~/bin/GamepadController/applaunch.sh");
	    }
	    
	    if(button == BUTTON_LB)
	    {
		  if(pressedOrReleased == PRESSED)
			  systemController->clickMouse(1);
		  else
			  systemController->unclickMouse(1);
	    }
	      if(button == BUTTON_RB)
	    {
		  if(pressedOrReleased == PRESSED)
			  systemController->clickMouse(3);
		  else
			  systemController->unclickMouse(3);
	    }
    }
  if (button == BUTTON_X && isLT_pressed && pressedOrReleased == PRESSED)
  {
	pressCtrlPlusAltPlusKey(17);
  }
  if (button == BUTTON_B && isLT_pressed && pressedOrReleased == PRESSED)
  {
	pressCtrlPlusAltPlusKey(31);
  }
  if  (button == BUTTON_Y && isLT_pressed && pressedOrReleased == PRESSED)
  {
      pressCtrlPlusAltPlusKey(18);
  }
    if (button == BUTTON_A && isLT_pressed && pressedOrReleased == PRESSED)
  {
      pressCtrlPlusAltPlusKey(16);
  }
  
  // Here implement handling of button events ;)
}

void JoypadHandler::handleAxis(JoypadAxis axis, int value)
{
  DEBUG << "Axis " << axis << " value = " << value;
      if(systemController->getApplicationOnTop().compare("steam")!=0)
    {
	    if(systemController->getApplicationOnTop().compare("chrome")==0)
	    {
		chromeShortcuts.chromeAxis( axis, value);

	    }
	  if(axis==AXIS_RIGHT_HORIZONTAL)
		{
		mouseSpeedX = calculateMouseSpeed (value, configStore);
		}
	  else if(axis == AXIS_RIGHT_VERTICAL)
		{
		mouseSpeedY = calculateMouseSpeed (value, configStore);
		}
	
    }
   if (axis ==AXIS_LT)
   {
     isLT_pressed = isLT_belowThreshold (value, configStore);
   }
   if ((axis ==AXIS_LEFT_HORIZONTAL) && isLT_pressed)
	{
		if (value >(-configStore->getSwitchDesktopLowerThreshold()) &&
		  value<configStore->getSwitchDesktopLowerThreshold()) 
		  flag =true; // isLeftHorizontalAxisInMiddle
		if ( (value<(-configStore->getSwitchDesktopHigherThreshold()) && flag)  ||
		  (value>configStore->getSwitchDesktopHigherThreshold() && flag))
		{
			LeftAxisHorizontalMovements (value, flag);
		}
		
	}
	

}

void JoypadHandler::handleTime() // once a 1/20 s
{
    DEBUG << "handleTime was called";
    if(systemController->getApplicationOnTop().compare("steam")!=0)
    {
	      systemController->moveMouse(mouseSpeedX, mouseSpeedY);
	  if(systemController->getApplicationOnTop().compare("chrome")==0)
	      chromeShortcuts.handleTime();
    }
}
void JoypadHandler::LeftAxisHorizontalMovements (int value, bool &flag)
	{
		if (value<(-configStore->getSwitchDesktopHigherThreshold()))
		{
			systemController->pressKey(42); // switchToDesktopToTheLeft
			systemController->pressKey(56);
			systemController->pressKey(30);
			systemController->releaseKey(30);
			systemController->releaseKey(56);
			systemController->releaseKey(42);
		}
        else if(value>configStore->getSwitchDesktopHigherThreshold())
		{
			systemController->pressKey(42); //
			systemController->pressKey(56);
			systemController->pressKey(32);
			systemController->releaseKey(32);
			systemController->releaseKey(56);
			systemController->releaseKey(42);
		}
		flag=false;
	}
