#include "JoypadHandler.hpp"
#include <iostream>

using namespace std;

JoypadHandler::JoypadHandler(ISystemController* p_systemController) :
  systemController(p_systemController)
{
	mouseSpeedX = 0;
	mouseSpeedY = 0;
}

void JoypadHandler::handleButton(JoypadButton button, PressedOrReleased pressedOrReleased)
{
  //cout << "Button " << button << " was " << pressedOrReleased << endl;
  
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
		mouseSpeedX = - value / 2048;
	}
  else if(axis == AXIS_RIGHT_VERTICAL)
	{
		mouseSpeedY = value / 2048;
	}
}

void JoypadHandler::handleTime() // once a 1/20 s
{
	systemController->moveMouse(mouseSpeedX, mouseSpeedY);
}
