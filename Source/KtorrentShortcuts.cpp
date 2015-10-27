#include "KtorrentShortcuts.hpp"
#include "IKeyPresser.hpp"
#include "ArrowsToArrowsPresser.hpp"

KtorrentShortcuts::KtorrentShortcuts(ISystemController* systemController,
                                     IConfigStore* configStore,
                                     IKeyPresser& keyPresser) :
    ApplicationShortcutsBase(systemController, configStore, keyPresser)
{
}

string KtorrentShortcuts::getApplication()
{
  return "ktorrent";
}

void KtorrentShortcuts::handleButton(JoypadButton button, PressedOrReleased pressedOrReleased, bool isLT_belowThreshold)
{
  if(pressedOrReleased != PRESSED)
    return;

  switch(button)
  {
    case BUTTON_B:
      keyPresser.pressAndReleaseKey(83);
      break;
    case BUTTON_A:
      keyPresser.pressCtrlPlusKey(31);
      break;
    case BUTTON_X:
      keyPresser.pressCtrlPlusKey(37);
      break;
    case BUTTON_Y:
      keyPresser.pressCtrlPlusKey(35);
      break;
  }
  arrowsToArrowsPresser.pressArrow(button);
}

void KtorrentShortcuts::handleAxis(JoypadAxis axis, int value, bool isLT_belowThreshold)
{
  if (axis==AXIS_LEFT_VERTICAL)
      mouseScrooler.setAxisValue(value);
}

void KtorrentShortcuts::handleTime()
{
  mouseScrooler.handleTime();
}
