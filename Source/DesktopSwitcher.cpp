#include "DesktopSwitcher.hpp"

DesktopSwitcher::DesktopSwitcher(IKeyPresser& p_keyPresser,
                                 IConfigStore& p_configStore) :
    keyPresser(p_keyPresser),
    configStore(p_configStore)
{
    isReadyForNextSwitch = true;
}

bool DesktopSwitcher::isAxisInMiddleZone(int value)
{
    return value > -configStore.getSwitchDesktopLowerThreshold() &&
           value <  configStore.getSwitchDesktopLowerThreshold();
}

void DesktopSwitcher::switchToTheLeft()
{
    keyPresser.pressKey(42);
    keyPresser.pressKey(56);
    keyPresser.pressAndReleaseKey(30);
    keyPresser.releaseKey(56);
    keyPresser.releaseKey(42);

    isReadyForNextSwitch=false;
}

void DesktopSwitcher::switchToTheRight()
{
    keyPresser.pressKey(42);
    keyPresser.pressKey(56);
    keyPresser.pressAndReleaseKey(32);
    keyPresser.releaseKey(56);
    keyPresser.releaseKey(42);

    isReadyForNextSwitch=false;
}

void DesktopSwitcher::handleAxis(JoypadAxis axis, int value, bool isLT_pressed)
{
    if (!isLT_pressed)
        return;

    if ( axis != AXIS_LEFT_HORIZONTAL)
        return;

    if (isAxisInMiddleZone(value))
        isReadyForNextSwitch = true;

    if (!isReadyForNextSwitch)
        return;

    if (value < (-configStore.getSwitchDesktopHigherThreshold()))
        switchToTheLeft();
    else if(value>configStore.getSwitchDesktopHigherThreshold())
        switchToTheRight();
}

