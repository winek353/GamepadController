#include <gtest/gtest.h>
#include "JoypadHandlerTestBase.hpp"


using namespace testing;

class DesktopSwitchingTests : public JoypadHandlerTestBase
{
public:
  DesktopSwitchingTests() :
      JoypadHandlerTestBase()
  {}

  void SetUp()
  {
      EXPECT_CALL(sysControllerMock, getApplicationOnTop()).WillRepeatedly(Return(std::string("plasma-desktop")));
      configStoreDefaultExpectations();
  }

  void configStoreDefaultExpectations()
  {
      EXPECT_CALL(configStoreMock, getReversedMouseSpeed()).WillRepeatedly(Return(2048));
      EXPECT_CALL(configStoreMock, getMouseDeadZoneSize()).WillRepeatedly(Return(2048));
  }

  void expectSwitchToLeftDesktop();
  void expectSwitchToRightDesktop();
protected:
};

void DesktopSwitchingTests::expectSwitchToLeftDesktop()
{
  EXPECT_CALL(sysControllerMock, pressKey(30));
  EXPECT_CALL(sysControllerMock, pressKey(42));
  EXPECT_CALL(sysControllerMock, pressKey(56));
  EXPECT_CALL(sysControllerMock, releaseKey(30));
  EXPECT_CALL(sysControllerMock, releaseKey(42));
  EXPECT_CALL(sysControllerMock, releaseKey(56));
}

void DesktopSwitchingTests::expectSwitchToRightDesktop()
{
  EXPECT_CALL(sysControllerMock, pressKey(32));
  EXPECT_CALL(sysControllerMock, pressKey(42));
  EXPECT_CALL(sysControllerMock, pressKey(56));
  EXPECT_CALL(sysControllerMock, releaseKey(32));
  EXPECT_CALL(sysControllerMock, releaseKey(42));
  EXPECT_CALL(sysControllerMock, releaseKey(56));
}

TEST_F(DesktopSwitchingTests, shouldSwitchDesktopToTheLeft_whenLeftAxisGoBelowThreshold)
{
  joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, 0);
  joypadHandler.handleAxis(AXIS_LT, 27888);
  expectSwitchToLeftDesktop();
  joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, -28667);
}

TEST_F(DesktopSwitchingTests, shouldSwitchDesktopToTheRight_whenLeftAxisGoAboveThreshold)
{
  joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, 0);
  joypadHandler.handleAxis(AXIS_LT, 27888);
  expectSwitchToRightDesktop();
  joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, 28667);
}

TEST_F(DesktopSwitchingTests, shouldNotSwitchToDesktopToTheLeft_ifLeftAxisDidntGoAboveThreshold)
{
  joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, 0);
  joypadHandler.handleAxis(AXIS_LT, 27888);
  expectSwitchToLeftDesktop();
  joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, -28667);
  joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, -28650);
}

TEST_F(DesktopSwitchingTests, shouldNotSwitchToDesktopToTheRight_ifLeftAxisDidntGoBelowThreshold)
{
  joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, 0);
  joypadHandler.handleAxis(AXIS_LT, 27888);
  expectSwitchToRightDesktop();
  joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, 28667);
  joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, 28650);
}

TEST_F(DesktopSwitchingTests, shouldAgainSwitchToDesktopToTheLeft_ifLeftAxisGoAboveThreshold)
{
  joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, 0);
  joypadHandler.handleAxis(AXIS_LT, 27888);
  expectSwitchToLeftDesktop();
  joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, -28667);
  joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, -24667);

  expectSwitchToLeftDesktop();
  joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, -28650);
}

TEST_F(DesktopSwitchingTests, shouldAgainSwitchToDesktopToTheRight_ifLeftAxisGoBelowThreshold)
{
  joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, 0);
  joypadHandler.handleAxis(AXIS_LT, 27888);

  expectSwitchToRightDesktop();
  joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, 28667);
  joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, 24667);

  expectSwitchToRightDesktop();
  joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, 28650);
}

TEST_F(DesktopSwitchingTests, shouldNotSwitchDesktop_whenAxisLtIsBelowThreshold)
{
    joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, 0);
    joypadHandler.handleAxis(AXIS_LT, 24888);
    joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, 28667);
    joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, -28667);
}

TEST_F(DesktopSwitchingTests, shouldNotSwitchDesktopToTheLeft_whenLtIsAboveChangedThreshold)
{
  EXPECT_CALL(configStoreMock, getLtPressedThreshold()).WillRepeatedly(Return(30000));
  joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, 0);
  joypadHandler.handleAxis(AXIS_LT, 27888);
  joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, -28667);
}
