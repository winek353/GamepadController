#pragma once
#include "IKeyPresser.hpp"
#include "JoypadAxis.hpp"
#include "IConfigStore.hpp"

class DesktopSwitcher
{
public:
    DesktopSwitcher(IKeyPresser&,IConfigStore&);
    void handleAxis(JoypadAxis, int, bool);
    void switchToTheLeft();
    void switchToTheRight();
    bool isAxisInMiddleZone(int);
private:
    IKeyPresser& keyPresser;
    IConfigStore& configStore;
    bool isReadyForNextSwitch;
};
