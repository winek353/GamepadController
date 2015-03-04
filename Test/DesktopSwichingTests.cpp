#include <gtest/gtest.h>
#include "SystemControllerMock.hpp"
#include "JoypadHandler.hpp"


using namespace testing;

class DesktopSwitchingTests : public Test
{
public:
  DesktopSwitchingTests() :
    sysConteollerMock(),
    joypadHandler(&sysConteollerMock)
  {}

  void SetUp()
  {
      EXPECT_CALL(sysConteollerMock, getApplicationOnTop()).WillRepeatedly(Return(std::string("plasma-desktop")));
  }

  void expectSwitchToLeftDesktop();
  void expectSwitchToRightDesktop();
protected:
  StrictMock<SystemControllerMock> sysConteollerMock;
  JoypadHandler joypadHandler;
};

void DesktopSwitchingTests::expectSwitchToLeftDesktop()
{
  EXPECT_CALL(sysConteollerMock, pressKey(30));
  EXPECT_CALL(sysConteollerMock, pressKey(42));
  EXPECT_CALL(sysConteollerMock, pressKey(56));
  EXPECT_CALL(sysConteollerMock, releaseKey(30));
  EXPECT_CALL(sysConteollerMock, releaseKey(42));
  EXPECT_CALL(sysConteollerMock, releaseKey(56));
}

void DesktopSwitchingTests::expectSwitchToRightDesktop()
{
  EXPECT_CALL(sysConteollerMock, pressKey(32));
  EXPECT_CALL(sysConteollerMock, pressKey(42));
  EXPECT_CALL(sysConteollerMock, pressKey(56));
  EXPECT_CALL(sysConteollerMock, releaseKey(32));
  EXPECT_CALL(sysConteollerMock, releaseKey(42));
  EXPECT_CALL(sysConteollerMock, releaseKey(56));
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
