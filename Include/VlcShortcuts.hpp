#pragma once
#include "ISystemController.hpp"
#include "JoypadButton.hpp"
#include "PressedOrReleased.hpp"
#include "JoypadAxis.hpp"
#include "ApplicationShortcutsBase.hpp"
#include "IConfigStore.hpp"
#include "IKeyPresser.hpp"

enum ScroolingInterval
{
  DEAD_ZONE,
  SLOW_FORWARD,
  MEDIUM_FORWARD,
  FAST_FORWARD,
  SLOW_BACKWARD,
  MEDIUM_BACKWARD,
  FAST_BACKWARD
};

class VlcShortcuts : public ApplicationShortcutsBase
{
public:
  VlcShortcuts(ISystemController*, IConfigStore*, IKeyPresser&);
  
  string getApplication();
  void handleButton(JoypadButton, PressedOrReleased, bool);
  void handleAxis(JoypadAxis, int, bool isLT_belowThreshold);
  void handleTime();
  void intervalCases(ScroolingInterval last, ScroolingInterval current);
  ScroolingInterval getScroolingInterval(int value);
private:
    ScroolingInterval lastScroolingInterval;
     IConfigStore* configStore;
};