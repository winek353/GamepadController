#include "JoypadButton.hpp"

std::ostream& operator<<(std::ostream& stream, JoypadButton button)
{
  switch(button)
  {
    case BUTTON_A: stream << "A"; break;
    case BUTTON_B: stream << "B"; break;
    case BUTTON_X: stream << "X"; break;
    case BUTTON_Y: stream << "Y"; break;
    case BUTTON_LB: stream << "LB"; break;
    case BUTTON_RB: stream << "RB"; break;
    case BUTTON_BACK: stream << "BACK"; break;
    case BUTTON_START: stream << "START"; break;
    case BUTTON_XBOX: stream << "XBOX"; break;
    case BUTTON_LEFT_JOY: stream << "LEFT_JOY"; break;
    case BUTTON_RIGHT_JOY: stream << "RIGHT_JOY"; break;
    case BUTTON_LEFT: stream << "LEFT"; break;
    case BUTTON_RIGHT: stream << "RIGHT"; break;
    case BUTTON_UP: stream << "UP"; break;
    case BUTTON_DOWN: stream << "DOWN"; break;
    default:
      stream << "UNKNOWN"; break;
  }
  return stream;
}