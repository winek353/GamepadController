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
    if(pressedOrReleased == PRESSED)
        return;

    if(isLT_belowThreshold==false)
    {
        switch(button)
        {
            case BUTTON_A:
                keyPresser.pressCtrlPlusKey(20);
                break;
            case BUTTON_B:
                keyPresser.pressCtrlPlusKey(17);
                break;
            case BUTTON_X:
                keyPresser.pressAndReleaseKey(57);
                break;
            case BUTTON_Y:
                keyPresser.pressAndReleaseKey(87);
                break;
            case BUTTON_LEFT:
                keyPresser.pressCtrlPlusKey(104);
                break;
            case BUTTON_RIGHT:
                keyPresser.pressCtrlPlusKey(109);
                break;
            case BUTTON_UP:
                keyPresser.pressCtrlPlusKey(13);
                break;
            case BUTTON_DOWN:
                keyPresser.pressCtrlPlusKey(12);
                break;
        }
    }
    else
    {
        switch(button)
        {
            case BUTTON_LEFT:
                keyPresser.pressAndReleaseKey(105);
                break;
            case BUTTON_RIGHT:
                keyPresser.pressAndReleaseKey(106);
                break;
        }
    }
}
void ChromeShortcuts::handleAxis(JoypadAxis axis, int value, bool isLT_belowThreshold)
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
   // horMovements();
}

void ChromeShortcuts::pressConditionalyArrows(bool moveOrNot,
                                              int frequency,
                                              int &eventCounter,
                                              int keyNegativeFreq,
                                              int keyPositiveFreq)
{
        if (frequency<0 && moveOrNot && eventCounter >= -frequency)
        {
            sysController->clickMouse(4);
            sysController->unclickMouse(4);
            eventCounter=0;
        }
        else if(frequency>0 && moveOrNot && eventCounter>= frequency)
        {
            sysController->clickMouse(5);
            sysController->unclickMouse(5);
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
