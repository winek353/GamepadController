#pragma once

class IConfigStore
{
public:
    virtual int getReversedMouseSpeed() = 0;
    virtual int getMouseDeadZoneSize() = 0;
    virtual int getLtPressedThreshold() = 0;
    virtual int getSwitchDesktopLowerThreshold() = 0;
    virtual int getSwitchDesktopHigherThreshold() = 0;
    virtual int getChromeReversedScroolingSpeed() = 0;
};
