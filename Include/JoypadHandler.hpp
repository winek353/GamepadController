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
  bool flag;
  void LeftAxisHorizontalMovements (int value, bool &flag);
  int mouseSpeedX, mouseSpeedY;
  ISystemController* systemController;
};
