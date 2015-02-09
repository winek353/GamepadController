#pragma once
#include <ostream>

enum PressedOrReleased
{
  PRESSED,
  RELEASED
};

std::ostream& operator<<(std::ostream& stream, PressedOrReleased state);