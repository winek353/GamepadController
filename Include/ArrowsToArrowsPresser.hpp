#pragma once
#include "JoypadButton.hpp"
#include "IKeyPresser.hpp"
#include "PressedOrReleased.hpp"

class ArrowsToArrowsPresser
{
public:
  ArrowsToArrowsPresser(IKeyPresser&);
  
  void pressArrow(JoypadButton button, PressedOrReleased pressedOrReleased);
private:
  IKeyPresser& keyPresser;
};
