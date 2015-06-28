#pragma once
#include "PressedOrReleased.hpp"
#include "JoypadButton.hpp"
#include "JoypadAxis.hpp"
#include "ISystemController.hpp"
#include "IConfigStore.hpp"
#include "ChromeShortcuts.hpp"
#include "DolphinShortcuts.hpp"
#include "VlcShortcuts.hpp"
#include "KeyPresser.hpp"
#include "MouseMover.hpp"


const int applicationShortcutsSize = 4;

class JoypadHandler
{
public:
  JoypadHandler(ISystemController*,
                IConfigStore*);
  ~JoypadHandler();

  void handleButton(JoypadButton, PressedOrReleased);
  void handleAxis(JoypadAxis, int);
  void handleTime();

private:
  void pressCtrlPlusAltPlusKey(int key);
  bool isLT_pressed;
  bool flag;
  void LeftAxisHorizontalMovements (int value, bool &flag);
  int mouseSpeedX, mouseSpeedY;
  ISystemController* systemController;
  IConfigStore* configStore;

  MouseMover mouseMover;
  KeyPresser keyPresser;
  
  
  IApplicationShortcuts* applicationShortcuts[applicationShortcutsSize];
  
};
