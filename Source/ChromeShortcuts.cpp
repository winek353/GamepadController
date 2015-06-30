#include "ChromeShortcuts.hpp"
#include "IKeyPresser.hpp"
#include <iostream>
using namespace std;
#include "Logger.hpp"
#include <cstdlib>


ChromeShortcuts::ChromeShortcuts(ISystemController* systemController,
                                 IConfigStore* configStore,
                                 IKeyPresser& keyPresser) :
    ApplicationShortcutsBase(systemController, configStore, keyPresser)
{
    frequencyHOR=0;
    eventCounterHOR=100;
    moveOrNotHOR=false;
    frequencyVER=0;
    eventCounterVER=100;
    moveOrNotVER=false;
}

void ChromeShortcuts::updateArrowsPressingParams(int value, bool &moveOrNot, int &frequency)
{
    int scroolingDeadZone = configStore->getChromeScroolingDeadZone();
    if (value>scroolingDeadZone||value< -scroolingDeadZone)
    {
        frequency=configStore->getChromeReversedScroolingSpeed()/value;
        moveOrNot=true;
    }
    else
        moveOrNot=false;
}

void ChromeShortcuts::handleButton(JoypadButton button, PressedOrReleased pressedOrReleased, bool isLT_belowThreshold)
{
    if (isLT_belowThreshold==false)
    {
        if(button == BUTTON_A)
        {
            if(pressedOrReleased == PRESSED)
	    {
		keyPresser.pressCtrlPlusKey(20);
	    }
        }
        if(button == BUTTON_B)
        {
	    if(pressedOrReleased == PRESSED)
	    {
                keyPresser.pressCtrlPlusKey(17);
	    }
        }
    }
    if(button == BUTTON_LEFT)
    {
          if(pressedOrReleased == PRESSED)
          {
              keyPresser.pressCtrlPlusKey(104);
          }
    }
    if(button == BUTTON_RIGHT)
    {
        if(pressedOrReleased == PRESSED)
        {
            keyPresser.pressCtrlPlusKey(109);
        }
    }
    if(button == BUTTON_UP)
    {
        if(pressedOrReleased == PRESSED)
        {
            keyPresser.pressCtrlPlusKey(13);
        }
    }
    if(button == BUTTON_DOWN)
    {
        if(pressedOrReleased == PRESSED)
        {
            keyPresser.pressCtrlPlusKey(12);
        }
    }
}
void ChromeShortcuts::handleAxis(JoypadAxis axis, int value)
{
    if (axis==AXIS_LEFT_VERTICAL)
    {
        updateArrowsPressingParams(value, moveOrNotVER, frequencyVER);
    }
    if (axis==AXIS_LEFT_HORIZONTAL)
    {
      updateArrowsPressingParams(value, moveOrNotHOR, frequencyHOR);
    }
}
void ChromeShortcuts::handleTime() // once a 1/20 s
{
    verMovements();
    horMovements();
}

void ChromeShortcuts::pressConditionalyArrows(bool moveOrNot,
                                              int frequency,
                                              int &eventCounter,
                                              int keyNegativeFreq,
                                              int keyPositiveFreq)
{
        if (frequency<0 && moveOrNot && eventCounter >= -frequency)
        {
            keyPresser.pressAndReleaseKey(keyNegativeFreq);
            eventCounter=0;
        }
        else if(frequency>0 && moveOrNot && eventCounter>= frequency)
        {
            keyPresser.pressAndReleaseKey(keyPositiveFreq);
            eventCounter=0;
        }
    eventCounter++;   
}

void ChromeShortcuts::verMovements()
{
    DEBUG << "verMovements " << eventCounterVER << " " << frequencyVER;
    pressConditionalyArrows(moveOrNotVER,
                            frequencyVER,
                            eventCounterVER,
                            103,
                            108);
}
void ChromeShortcuts::horMovements()
{
    DEBUG << "horMovements " << eventCounterHOR << " " << frequencyHOR;
    pressConditionalyArrows(moveOrNotHOR,
                            frequencyHOR,
                            eventCounterHOR,
                            105,
                            106);
}

string ChromeShortcuts::getApplication()
{
  return "chrome";
}
