#pragma once
#include <ostream>

enum JoypadAxis
{
  AXIS_LT,
  AXIS_RT,
  AXIS_LEFT_HORIZONTAL,
  AXIS_LEFT_VERTICAL,
  AXIS_RIGHT_HORIZONTAL,
  AXIS_RIGHT_VERTICAL
};

std::ostream& operator<<(std::ostream& stream, JoypadAxis axis);
