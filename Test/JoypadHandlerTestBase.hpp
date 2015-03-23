#pragma once
#include "SystemControllerMock.hpp"
#include "ConfigStoreMock.hpp"
#include "JoypadHandler.hpp"

using namespace testing;

class JoypadHandlerTestBase : public Test
{
public:
    JoypadHandlerTestBase() :
        joypadHandler(&sysControllerMock,
                      &configStoreMock)
    {
    }

    void configStoreDefaultExpectations()
    {
        EXPECT_CALL(configStoreMock, getReversedMouseSpeed()).WillRepeatedly(Return(2048));
        EXPECT_CALL(configStoreMock, getMouseDeadZoneSize()).WillRepeatedly(Return(2048));
	EXPECT_CALL(configStoreMock, getLtPressedThreshold()).WillRepeatedly(Return(25000));
	
	EXPECT_CALL(configStoreMock, getSwitchDesktopLowerThreshold()).WillRepeatedly(Return(25000));
	EXPECT_CALL(configStoreMock, getSwitchDesktopHigherThreshold()).WillRepeatedly(Return(28000));

	EXPECT_CALL(configStoreMock, getChromeReversedScroolingSpeed()).WillRepeatedly(Return(128000));
	EXPECT_CALL(configStoreMock, getDolphinReversedScroolSpeed()).WillRepeatedly(Return(128000));
	
	EXPECT_CALL(configStoreMock, getVlcSlowScroolThreshold()).WillRepeatedly(Return(6000));
	EXPECT_CALL(configStoreMock, getVlcMediumScroolThreshold()).WillRepeatedly(Return(13000));
	EXPECT_CALL(configStoreMock, getVlcFastScroolThreshold()).WillRepeatedly(Return(25000));
    }
    
    void ignoreMouseMovement()
    {
	EXPECT_CALL(sysControllerMock, moveMouse(_,_)).Times(AnyNumber());
    }

protected:
    StrictMock<SystemControllerMock> sysControllerMock;
    StrictMock<ConfigStoreMock> configStoreMock;
    JoypadHandler joypadHandler;
};
