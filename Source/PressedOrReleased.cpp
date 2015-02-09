#include "PressedOrReleased.hpp"


std::ostream& operator<<(std::ostream& stream, PressedOrReleased state)
{
  switch(state)
  {
    case PRESSED: stream << "PRESSED"; break;
    case RELEASED: stream << "RELEASED"; break;
  }
  
  return stream;
}