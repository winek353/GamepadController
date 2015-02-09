#pragma once
#include <ostream>

enum JoypadButton
{
  BUTTON_A,
  BUTTON_B,
  BUTTON_X,
  BUTTON_Y,
  BUTTON_START,
  BUTTON_BACK,
  BUTTON_XBOX,
  BUTTON_LB,
  BUTTON_RB,
  BUTTON_LEFT,
  BUTTON_RIGHT,
  BUTTON_UP,
  BUTTON_DOWN,
  BUTTON_LEFT_JOY,
  BUTTON_RIGHT_JOY
};

std::ostream& operator<<(std::ostream& stream, JoypadButton button);