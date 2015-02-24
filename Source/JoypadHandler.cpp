#include "JoypadHandler.hpp"
#include <iostream>

using namespace std;

JoypadHandler::JoypadHandler(ISystemController* p_systemController) :
  systemController(p_systemController)
{
	mouseSpeedX = 0;
	mouseSpeedY = 0;
	flag = true;
    screenReadyToMove = false;
}
int calculateMouseSpeed (int value)
    {
        if (value>= 2048) return (value-2048)/2048;
        else if(value<=-2048) return (value+2048)/2048;
        else return 0;
    }
bool screenReady (int value)
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
void JoypadHandler::chromeButtons(JoypadButton button, PressedOrReleased pressedOrReleased)
    {
    if(button == BUTTON_A)
    {
      if(pressedOrReleased == PRESSED)
      {
          systemController->pressKey(29);
          systemController->pressKey(20);
          systemController->releaseKey(20);
          systemController->releaseKey(29);
      }
    }
    if(button == BUTTON_B)
    {
      if(pressedOrReleased == PRESSED)
      {
          systemController->pressKey(29);
          systemController->pressKey(17);
          systemController->releaseKey(17);
          systemController->releaseKey(29);
       }
    }
    if(button == BUTTON_LEFT)
    {
      if(pressedOrReleased == PRESSED)
      {
          systemController->pressKey(29);
          systemController->pressKey(104);
          systemController->releaseKey(104);
          systemController->releaseKey(29);
      }
    }
    if(button == BUTTON_RIGHT)
    {
      if(pressedOrReleased == PRESSED)
      {
          systemController->pressKey(29);
          systemController->pressKey(109);
          systemController->releaseKey(109);
          systemController->releaseKey(29);
       }
    }
    if(button == BUTTON_UP)
    {
      if(pressedOrReleased == PRESSED)
      {
          systemController->pressKey(29);
          systemController->pressKey(13);
          systemController->releaseKey(13);
          systemController->releaseKey(29);
      }
    }
    if(button == BUTTON_DOWN)
    {
      if(pressedOrReleased == PRESSED)
      {
          systemController->pressKey(29);
          systemController->pressKey(12);
          systemController->releaseKey(12);
          systemController->releaseKey(29);
      }
    }

    }

void JoypadHandler::handleButton(JoypadButton button, PressedOrReleased pressedOrReleased)
{
  //cout << "Button " << button << " was " << pressedOrReleased << endl;
  if(systemController->getApplicationOnTop().compare("chrome")==0)
  {
      chromeButtons(button, pressedOrReleased);
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
  
  // Here implement handling of button events ;)
}

void JoypadHandler::handleAxis(JoypadAxis axis, int value)
{
  //cout << "Axis " << axis << " value = " << value << endl;
  if(axis==AXIS_RIGHT_HORIZONTAL)
	{
        mouseSpeedX = calculateMouseSpeed (value);
	}
  else if(axis == AXIS_RIGHT_VERTICAL)
	{
        mouseSpeedY = calculateMouseSpeed (value);
	}
   if (axis ==AXIS_LT)
   {
     screenReadyToMove = screenReady (value);
   }
   if ((axis ==AXIS_LEFT_HORIZONTAL)&&screenReadyToMove)
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
	systemController->moveMouse(mouseSpeedX, mouseSpeedY);
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
