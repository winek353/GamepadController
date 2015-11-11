#include "ArrowsToArrowsPresser.hpp"

ArrowsToArrowsPresser::ArrowsToArrowsPresser(IKeyPresser& p_keyPresser) :
  keyPresser(p_keyPresser)
{
}

void ArrowsToArrowsPresser::pressArrow(JoypadButton button, PressedOrReleased pressedOrReleased)
{
    if(pressedOrReleased == PRESSED)
    {
      switch(button)
      {
        case BUTTON_LEFT:
          keyPresser.pressKey(105);
          break;
        case BUTTON_RIGHT:
          keyPresser.pressKey(106);
          break;
        case BUTTON_UP:
          keyPresser.pressKey(103);
          break;
        case BUTTON_DOWN:
          keyPresser.pressKey(108);
          break;
      }
    }
    else
    {
      switch(button)
      {
        case BUTTON_LEFT:
          keyPresser.releaseKey(105);
          break;
        case BUTTON_RIGHT:
          keyPresser.releaseKey(106);
          break;
        case BUTTON_UP:
          keyPresser.releaseKey(103);
          break;
        case BUTTON_DOWN:
          keyPresser.releaseKey(108);
          break;
      }
    }
}

