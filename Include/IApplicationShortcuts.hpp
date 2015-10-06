#pragma once
#include <string>
using namespace std;
#include "PressedOrReleased.hpp"
#include "JoypadButton.hpp"
#include "JoypadAxis.hpp"

class IApplicationShortcuts
{
public:
  virtual string getApplication() = 0;
  virtual void handleButton(JoypadButton, PressedOrReleased, bool) = 0;
  virtual void handleAxis(JoypadAxis, int, bool) = 0;
  virtual void handleTime() = 0;
};
