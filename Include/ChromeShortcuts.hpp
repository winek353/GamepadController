#pragma once
#include "ISystemController.hpp"
#include "JoypadButton.hpp"
#include "PressedOrReleased.hpp"
#include "JoypadAxis.hpp"
#include "IApplicationShortcuts.hpp"
#include "IConfigStore.hpp"

class ChromeShortcuts : public IApplicationShortcuts
{
public:
    ChromeShortcuts(ISystemController*,IConfigStore*);

    string getApplication();
    void handleButton(JoypadButton button, PressedOrReleased pressedOrReleased, bool isLT_belowThreshold);
    void handleAxis(JoypadAxis axis, int value);
    void handleTime();
    void verMovements();
    void horMovements();
private:
    ISystemController* systemController;
    int  frequencyHOR;
    int eventCounterHOR;
    bool moveOrNotHOR;
    int  frequencyVER;
    int eventCounterVER;
    bool moveOrNotVER;
    void pressCtrlPlusKey(int);
    void updateArrowsPressingParams(int value, bool &moveOrNot, int &frequency);
    void pressConditionalyArrows(bool moveOrNot,
                                 int frequency,
                                 int &eventCounter,
                                 int keyNegativeFreq,
                                 int keyPositiveFreq);
    IConfigStore* configStore;
};
