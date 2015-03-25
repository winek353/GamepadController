#pragma once
#include "ISystemController.hpp"
#include "JoypadButton.hpp"
#include "PressedOrReleased.hpp"
#include "JoypadAxis.hpp"
#include "IApplicationShortcuts.hpp"
#include "IConfigStore.hpp"

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
class VlcShortcuts : public IApplicationShortcuts
{
public:
  VlcShortcuts(ISystemController*, IConfigStore*);
  
  string getApplication();
  void handleButton(JoypadButton, PressedOrReleased, bool);
  void handleAxis(JoypadAxis, int);
  void handleTime();
  void intervalCases(ScroolingInterval last, ScroolingInterval current);
  ScroolingInterval getScroolingInterval(int value);
private:
    ScroolingInterval lastScroolingInterval;
    ISystemController* systemController;
     IConfigStore* configStore;
};