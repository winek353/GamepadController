#include "MouseScrooler.hpp"

MouseScrooler::MouseScrooler(IConfigStore& p_configStore, ISystemController& p_sysController) :
  configStore(p_configStore),
  sysController(p_sysController)
{
  frequency=0;
  eventCounter=100;
  moveOrNot=false;
}

void MouseScrooler::setAxisValue(int value)
{
  int scroolingDeadZone = configStore.getChromeScroolingDeadZone();
  if (value>scroolingDeadZone||value< -scroolingDeadZone)
  {
    frequency=configStore.getChromeReversedScroolingSpeed()/value;
    moveOrNot=true;
  }
  else
    moveOrNot=false;
}

void MouseScrooler::handleTime()
{
  if (frequency<0 && moveOrNot && eventCounter >= -frequency)
  {
    sysController.clickMouse(4);
    sysController.unclickMouse(4);
    eventCounter=0;
  }
  else if(frequency>0 && moveOrNot && eventCounter>= frequency)
  {
    sysController.clickMouse(5);
    sysController.unclickMouse(5);
    eventCounter=0;
  }
  eventCounter++;  
}
