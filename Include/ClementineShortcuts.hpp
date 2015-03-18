#pragma once
#include "ISystemController.hpp"
#include "JoypadButton.hpp"
#include "PressedOrReleased.hpp"
#include "JoypadAxis.hpp"
#include "IApplicationShortcuts.hpp"

class ClementineShortcuts : public IApplicationShortcuts
{
  public:
  ClementineShortcuts(ISystemController* systemController);
  virtual string getApplication();
  virtual void handleButton(JoypadButton, PressedOrReleased, bool);
  virtual void handleAxis(JoypadAxis, int);
  virtual void handleTime();
private:
   ISystemController* systemController;
    void pressCtrlPlusKey(int);
    void pressCtrlPlusShiftPlusKey(int key);
};