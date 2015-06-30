#include "VlcShortcuts.hpp"
#include <iostream>
using namespace std;
#include "Logger.hpp"
#include <cstdlib>

VlcShortcuts::VlcShortcuts(ISystemController* systemController,
                           IConfigStore* p_configStore,
                           IKeyPresser& p_keyPresser) :
    ApplicationShortcutsBase(systemController, configStore, p_keyPresser)
{
    configStore=p_configStore;
    lastScroolingInterval = DEAD_ZONE;
}

void VlcShortcuts::intervalCases(ScroolingInterval last, ScroolingInterval current)
{
  DEBUG << "vlc scrooling: last interval = " << last << " current = " << current;
  if(last != current)
  {
    switch(last)
    {
      case FAST_FORWARD:
	keyPresser.releaseKey(29);
	keyPresser.releaseKey(106);
	break;
      case MEDIUM_FORWARD:
	keyPresser.releaseKey(56);
	keyPresser.releaseKey(106);
	break;
      case SLOW_FORWARD:
	keyPresser.releaseKey(42);
	keyPresser.releaseKey(106);
	break;
      case SLOW_BACKWARD:
	keyPresser.releaseKey(42);
	keyPresser.releaseKey(105);
	break;
      case MEDIUM_BACKWARD:
	keyPresser.releaseKey(56);
	keyPresser.releaseKey(105);
	break;
      case FAST_BACKWARD:
	keyPresser.releaseKey(29);
	keyPresser.releaseKey(105);
	break;
    }
    
    switch(current)
    {
      case FAST_FORWARD:
	keyPresser.pressKey(29);
	keyPresser.pressKey(106);
	break;
      case MEDIUM_FORWARD:
	keyPresser.pressKey(56);
	keyPresser.pressKey(106);
	break;
    case SLOW_FORWARD:
        DEBUG << "AAA " << &keyPresser;
	keyPresser.pressKey(42);
        DEBUG << "BBB";
	keyPresser.pressKey(106);
        DEBUG << "CCC";
	break;
      case SLOW_BACKWARD:
	keyPresser.pressKey(42);
	keyPresser.pressKey(105);
	break;
      case MEDIUM_BACKWARD:
	keyPresser.pressKey(56);
	keyPresser.pressKey(105);
	break;
      case FAST_BACKWARD:
	keyPresser.pressKey(29);
	keyPresser.pressKey(105);
	break;
    }
  }
}

void VlcShortcuts::handleButton(JoypadButton button, PressedOrReleased pressedOrReleased, bool isLT_belowThreshold)
{
    if (button == BUTTON_X)
    {
        if(pressedOrReleased == PRESSED)	
        {
            keyPresser.pressAndReleaseKey(57);	
        }
    }
    else if (button == BUTTON_B)
    {
        if(pressedOrReleased == PRESSED)
        {
            keyPresser.pressAndReleaseKey(31);
        }
    }
    else if (button == BUTTON_START)
    {
        if(pressedOrReleased == PRESSED)	
        {
            keyPresser.pressAndReleaseKey(33);	
        }
    }
}
  

string VlcShortcuts::getApplication()
{
  return "vlc";
}

ScroolingInterval VlcShortcuts::getScroolingInterval(int value)
{
  if( value >= configStore->getVlcFastScroolThreshold())
    return FAST_FORWARD;
  if( value >= configStore->getVlcMediumScroolThreshold())
    return MEDIUM_FORWARD;
  if( value >= configStore->getVlcSlowScroolThreshold())
    return SLOW_FORWARD;
  
  if( value <= -configStore->getVlcFastScroolThreshold())
    return FAST_BACKWARD;
  if( value <= -configStore->getVlcMediumScroolThreshold())
    return MEDIUM_BACKWARD;
  if( value <= -configStore->getVlcSlowScroolThreshold())
    return SLOW_BACKWARD;
  
  return DEAD_ZONE;
}

void VlcShortcuts::handleAxis(JoypadAxis axis, int value)
{
    if (axis == AXIS_LEFT_HORIZONTAL )
    {
        ScroolingInterval currentInterval = getScroolingInterval(value);
        intervalCases(lastScroolingInterval, currentInterval);
        lastScroolingInterval = currentInterval;
    }
}

void VlcShortcuts::handleTime()
{
  
}
