#pragma once
#include "JoypadButton.hpp"
#include "IKeyPresser.hpp"

class ArrowsToArrowsPresser
{
public:
  ArrowsToArrowsPresser(IKeyPresser&);
  
  void pressArrow(JoypadButton button);
private:
  IKeyPresser& keyPresser;
};
