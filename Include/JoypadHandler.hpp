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
#include "DesktopSwitcher.hpp"
#include "InactivityFilter.hpp"
#include "ButtonsAndAxisStateKeeper.hpp"
#include "PreciseMouseMover.hpp"

const int applicationShortcutsSize = 5;

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
  bool isLT_pressed, isRT_pressed;
  int mouseSpeedX, mouseSpeedY;
  ISystemController* systemController;
  IConfigStore* configStore;

  MouseMover mouseMover;
  PreciseMouseMover preciseMouseMover;
  KeyPresser keyPresser;
  DesktopSwitcher desktopSwitcher;
  InactivityFilter inactivityFilter;
  ButtonsAndAxisStateKeeper buttonsAndAxisStateKeeper;
  
  
  IApplicationShortcuts* applicationShortcuts[applicationShortcutsSize];
  
};
