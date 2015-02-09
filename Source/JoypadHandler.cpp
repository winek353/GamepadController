#include "JoypadHandler.hpp"
#include <iostream>

using namespace std;

JoypadHandler::JoypadHandler(ISystemController* p_systemController) :
  systemController(p_systemController)
{
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
  
  // Here implement handling of button events ;)
}

void JoypadHandler::handleAxis(JoypadAxis axis, int value)
{
  //cout << "Axis " << axis << " value = " << value << endl;
  // Here implement handling of axis events ;)
}

void JoypadHandler::handleTime() // once a 1/100 s
{
  //cout << "Time event!" << endl;
  // Here implement handling of time event ;)
}
