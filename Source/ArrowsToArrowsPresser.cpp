#include "ArrowsToArrowsPresser.hpp"

ArrowsToArrowsPresser::ArrowsToArrowsPresser(IKeyPresser& p_keyPresser) :
  keyPresser(p_keyPresser)
{
}

void ArrowsToArrowsPresser::pressArrow(JoypadButton button)
{
  switch(button)
  {
    case BUTTON_LEFT:
      keyPresser.pressAndReleaseKey(105);
      break;
    case BUTTON_RIGHT:
      keyPresser.pressAndReleaseKey(106);
      break;
    case BUTTON_UP:
      keyPresser.pressAndReleaseKey(103);
      break;
    case BUTTON_DOWN:
      keyPresser.pressAndReleaseKey(108);
      break;
  }
}

