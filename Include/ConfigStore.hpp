#pragma once
#include "IConfigStore.hpp"

class ConfigStore : public IConfigStore
{
public:
    virtual int getReversedMouseSpeed();
    virtual int getMouseDeadZoneSize();
    virtual int getLtPressedThreshold();
    virtual int getSwitchDesktopLowerThreshold();
    virtual int getSwitchDesktopHigherThreshold();
    virtual int getChromeReversedScroolingSpeed();
    virtual int getChromeScroolingDeadZone();
    virtual int getDolphinReversedScroolSpeed();
    
    virtual int getVlcSlowScroolThreshold();
    virtual int getVlcMediumScroolThreshold();
    virtual int getVlcFastScroolThreshold();
};
