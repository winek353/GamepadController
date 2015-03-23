#pragma once
#include <gmock/gmock.h>
#include "IConfigStore.hpp"

class ConfigStoreMock : public IConfigStore
{
public:
    MOCK_METHOD0(getReversedMouseSpeed, int());
    MOCK_METHOD0(getMouseDeadZoneSize, int());
    MOCK_METHOD0(getLtPressedThreshold, int());
    MOCK_METHOD0(getSwitchDesktopLowerThreshold, int());
    MOCK_METHOD0(getSwitchDesktopHigherThreshold, int());
    MOCK_METHOD0(getChromeReversedScroolingSpeed, int());
    MOCK_METHOD0(getDolphinReversedScroolSpeed, int());
    
    MOCK_METHOD0(getVlcSlowScroolThreshold, int());
    MOCK_METHOD0(getVlcMediumScroolThreshold, int());
    MOCK_METHOD0(getVlcFastScroolThreshold, int());
};
