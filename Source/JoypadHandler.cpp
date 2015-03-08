#include "JoypadHandler.hpp"
#include <iostream>
#include "Logger.hpp"

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
int calculateMouseSpeed (int value)
    {
        if (value>= 2048) return (value-2048)/2048;
        else if(value<=-2048) return (value+2048)/2048;
        else return 0;
    }
bool isLT_belowThreshold (int value)
    {
        if(value>=25000)
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
		mouseSpeedX = calculateMouseSpeed (value);
		}
	  else if(axis == AXIS_RIGHT_VERTICAL)
		{
		mouseSpeedY = calculateMouseSpeed (value);
		}
	
    }
   if (axis ==AXIS_LT)
   {
     isLT_pressed = isLT_belowThreshold (value);
   }
   if ((axis ==AXIS_LEFT_HORIZONTAL)&&isLT_pressed)
	{
		if (value >(-25000)&&value<25000) flag =true; // isLeftHorizontalAxisInMiddle
		if ( (value<(-28000)&&flag)  ||  (value>28000&&flag))
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
		if (value<(-28000))
		{
			systemController->pressKey(42); // switchToDesktopToTheLeft
			systemController->pressKey(56);
			systemController->pressKey(30);
			systemController->releaseKey(30);
			systemController->releaseKey(56);
			systemController->releaseKey(42);
		}
        else if(value>28000)
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
