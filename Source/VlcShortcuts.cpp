#include "VlcShortcuts.hpp"
#include <iostream>
using namespace std;
#include "Logger.hpp"
#include <cstdlib>

VlcShortcuts::VlcShortcuts(ISystemController* systemController, IConfigStore* p_configStore)
{
    this->systemController = systemController;
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
	systemController->releaseKey(29);
	systemController->releaseKey(106);
	break;
      case MEDIUM_FORWARD:
	systemController->releaseKey(56);
	systemController->releaseKey(106);
	break;
      case SLOW_FORWARD:
	systemController->releaseKey(42);
	systemController->releaseKey(106);
	break;
      case SLOW_BACKWARD:
	systemController->releaseKey(42);
	systemController->releaseKey(105);
	break;
      case MEDIUM_BACKWARD:
	systemController->releaseKey(56);
	systemController->releaseKey(105);
	break;
      case FAST_BACKWARD:
	systemController->releaseKey(29);
	systemController->releaseKey(105);
	break;
    }
    
    switch(current)
    {
      case FAST_FORWARD:
	systemController->pressKey(29);
	systemController->pressKey(106);
	break;
      case MEDIUM_FORWARD:
	systemController->pressKey(56);
	systemController->pressKey(106);
	break;
      case SLOW_FORWARD:
	systemController->pressKey(42);
	systemController->pressKey(106);
	break;
      case SLOW_BACKWARD:
	systemController->pressKey(42);
	systemController->pressKey(105);
	break;
      case MEDIUM_BACKWARD:
	systemController->pressKey(56);
	systemController->pressKey(105);
	break;
      case FAST_BACKWARD:
	systemController->pressKey(29);
	systemController->pressKey(105);
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
      systemController->pressKey(57);	
      systemController->releaseKey(57);
    }
  }
  if (button == BUTTON_B)
  {
    if(pressedOrReleased == PRESSED)
    {
      systemController->pressKey(31);
      systemController->releaseKey(31);
    }
  }
  if (button == BUTTON_START)
  {
    if(pressedOrReleased == PRESSED)	
    {
      systemController->pressKey(33);	
      systemController->releaseKey(33);
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
  ScroolingInterval currentInterval = getScroolingInterval(value);
  intervalCases(lastScroolingInterval, currentInterval);
  lastScroolingInterval = currentInterval;
}

void VlcShortcuts::handleTime()
{
  
}
