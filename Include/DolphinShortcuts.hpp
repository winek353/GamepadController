#pragma once
#include "ISystemController.hpp"
#include "JoypadButton.hpp"
#include "PressedOrReleased.hpp"
#include "JoypadAxis.hpp"
#include "IApplicationShortcuts.hpp"

class DolphinShortcuts : public IApplicationShortcuts
{
public:
  DolphinShortcuts(ISystemController*);
  
  string getApplication();
  void handleButton(JoypadButton, PressedOrReleased, bool);
  void handleAxis(JoypadAxis, int, bool isLT_belowThreshold);
  void handleTime();
private:
    ISystemController* systemController;
};