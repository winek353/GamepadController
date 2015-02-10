#pragma once
#include "PressedOrReleased.hpp"
#include "JoypadButton.hpp"
#include "JoypadAxis.hpp"
#include "SystemController.hpp"

class JoypadHandler
{
public:
  JoypadHandler(ISystemController*);
  void handleButton(JoypadButton, PressedOrReleased);
  void handleAxis(JoypadAxis, int);
  void handleTime();

private:
  int mouseSpeedX, mouseSpeedY;
  ISystemController* systemController;
};
