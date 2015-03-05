#include "ChromeShortcuts.hpp"
#include <iostream>
using namespace std;
#include "Logger.hpp"

ChromeShortcuts::ChromeShortcuts(ISystemController* systemController)
{
    this->systemController = systemController;
    frequencyHOR=0;
    eventCounterHOR=100;
    moveOrNotHOR=false;
    frequencyVER=0;
    eventCounterVER=100;
    moveOrNotVER=false;
}

void ChromeShortcuts::chromeButtons(JoypadButton button, PressedOrReleased pressedOrReleased)
{
    if(button == BUTTON_A)
    {
      if(pressedOrReleased == PRESSED)
      {
          systemController->pressKey(29);
          systemController->pressKey(20);
          systemController->releaseKey(20);
          systemController->releaseKey(29);
      }
    }
    if(button == BUTTON_B)
    {
      if(pressedOrReleased == PRESSED)
      {
          systemController->pressKey(29);
          systemController->pressKey(17);
          systemController->releaseKey(17);
          systemController->releaseKey(29);
       }
    }
    if(button == BUTTON_LEFT)
    {
      if(pressedOrReleased == PRESSED)
      {
          systemController->pressKey(29);
          systemController->pressKey(104);
          systemController->releaseKey(104);
          systemController->releaseKey(29);
      }
    }
    if(button == BUTTON_RIGHT)
    {
      if(pressedOrReleased == PRESSED)
      {
          systemController->pressKey(29);
          systemController->pressKey(109);
          systemController->releaseKey(109);
          systemController->releaseKey(29);
       }
    }
    if(button == BUTTON_UP)
    {
      if(pressedOrReleased == PRESSED)
      {
          systemController->pressKey(29);
          systemController->pressKey(13);
          systemController->releaseKey(13);
          systemController->releaseKey(29);
      }
    }
    if(button == BUTTON_DOWN)
    {
      if(pressedOrReleased == PRESSED)
      {
          systemController->pressKey(29);
          systemController->pressKey(12);
          systemController->releaseKey(12);
          systemController->releaseKey(29);
      }
    }

}
void ChromeShortcuts::chromeAxis(JoypadAxis axis, int value)
{
    if (axis==AXIS_LEFT_VERTICAL)
    {
      if (value>2000||value< -2000)
      {
          frequencyVER=128000/value;
          moveOrNotVER=true;
      }
      else
          moveOrNotVER=false;
    }
    if (axis==AXIS_LEFT_HORIZONTAL)
    {
      if (value>2000||value< -2000)
      {
          frequencyHOR=128000/value;
          moveOrNotHOR=true;
      }
      else
          moveOrNotHOR=false;
    }
}
void ChromeShortcuts::handleTime() // once a 1/20 s
{
    verMovements();
    horMovements();


}
void ChromeShortcuts::verMovements()
{
    DEBUG << "verMovements " << eventCounterVER << " " << frequencyVER;
    if (moveOrNotVER && eventCounterVER>=frequencyVER)
    {
        if (frequencyVER<0)
        {
            systemController->pressKey(103);
            systemController->releaseKey(103);
            eventCounterVER=0;
        }
        else if(frequencyVER>0)
        {
             systemController->pressKey(108);
             systemController->releaseKey(108);
             eventCounterVER=0;
        }
    }
    eventCounterVER++;
}
void ChromeShortcuts::horMovements()
{
    DEBUG << "horMovements " << eventCounterHOR << " " << frequencyHOR;
    if (moveOrNotHOR && eventCounterHOR>=frequencyHOR)
    {
        if (frequencyHOR<0)
        {
            systemController->pressKey(105);
            systemController->releaseKey(105);
            eventCounterHOR=0;
        }
        else if(frequencyHOR>0)
        {
             systemController->pressKey(106);
             systemController->releaseKey(106);
             eventCounterHOR=0;
        }
    }
    eventCounterHOR++;
}
