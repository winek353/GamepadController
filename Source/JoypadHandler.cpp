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
  // Here implement handling of button events ;)
}

void JoypadHandler::handleAxis(JoypadAxis axis, int value)
{
  //cout << "Axis " << axis << " value = " << value << endl;
  // Here implement handling of axis events ;)
}

void JoypadHandler::handleTime()
{
  //cout << "Time event!" << endl;
  // Here implement handling of time event ;)
}
