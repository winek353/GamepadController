#include "JoypadAxis.hpp"

std::ostream& operator<<(std::ostream& stream, JoypadAxis axis)
{
  switch(axis)
  {
    case AXIS_LT: stream << "LT"; break;
    case AXIS_RT: stream << "RT"; break;
    case AXIS_LEFT_HORIZONTAL: stream << "LEFT_HORIZONTAL"; break;
    case AXIS_LEFT_VERTICAL: stream << "LEFT_VERTICAL"; break;
    case AXIS_RIGHT_HORIZONTAL: stream << "RIGHT_HORIZONTAL"; break;
    case AXIS_RIGHT_VERTICAL: stream << "RIGHT_VERTICAL"; break;
  }
}
