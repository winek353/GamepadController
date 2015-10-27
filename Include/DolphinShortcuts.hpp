#pragma once
#include "ISystemController.hpp"
#include "JoypadButton.hpp"
#include "PressedOrReleased.hpp"
#include "JoypadAxis.hpp"
#include "ApplicationShortcutsBase.hpp"

class DolphinShortcuts : public ApplicationShortcutsBase
{
public:
  DolphinShortcuts(ISystemController*,
                    IConfigStore*,
                    IKeyPresser&);
  
  string getApplication();
  void handleButton(JoypadButton, PressedOrReleased, bool);
  void handleAxis(JoypadAxis, int, bool isLT_belowThreshold);
  void handleTime();
};