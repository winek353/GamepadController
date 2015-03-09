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
    }

protected:
    StrictMock<SystemControllerMock> sysControllerMock;
    StrictMock<ConfigStoreMock> configStoreMock;
    JoypadHandler joypadHandler;
};
