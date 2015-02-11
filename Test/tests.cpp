#include <gtest/gtest.h>
#include "SystemControllerMock.hpp"
#include "JoypadHandler.hpp"

using namespace testing;

class JoypadHandlerTestSuite : public Test
{
public:
  JoypadHandlerTestSuite() :
    sysConteollerMock(),
    joypadHandler(&sysConteollerMock)
  {}
  
  void expectSwitchToLeftDesktop();
  void expectSwitchToRightDesktop();
protected:
  SystemControllerMock sysConteollerMock;
  JoypadHandler joypadHandler;
};

TEST_F(JoypadHandlerTestSuite, shouldClickLeftMouseButton_whenLBisPressed)
{
  EXPECT_CALL(sysConteollerMock, clickMouse(1));
  joypadHandler.handleButton(BUTTON_LB, PRESSED);

  EXPECT_CALL(sysConteollerMock, unclickMouse(1));
  joypadHandler.handleButton(BUTTON_LB, RELEASED);
}

TEST_F(JoypadHandlerTestSuite, shouldClickRightMouseButton_whenRBisPressed)
{
  EXPECT_CALL(sysConteollerMock, clickMouse(3));
  joypadHandler.handleButton(BUTTON_RB, PRESSED);

  EXPECT_CALL(sysConteollerMock, unclickMouse(3));
  joypadHandler.handleButton(BUTTON_RB, RELEASED);
}

TEST_F(JoypadHandlerTestSuite, shouldMoveMouseX_whenAxisRightHorizontalIsMoved)
{
  joypadHandler.handleAxis(AXIS_RIGHT_HORIZONTAL, 3*2048);
  EXPECT_CALL(sysConteollerMock, moveMouse(-3,0));
  joypadHandler.handleTime();

  joypadHandler.handleAxis(AXIS_RIGHT_HORIZONTAL, -5*2048);
  EXPECT_CALL(sysConteollerMock, moveMouse(5,0));
  joypadHandler.handleTime();
}

TEST_F(JoypadHandlerTestSuite, shouldMoveMouseY_whenAxisRightVertcalIsMoved)
{
  joypadHandler.handleAxis(AXIS_RIGHT_VERTICAL, 3*2048);
  EXPECT_CALL(sysConteollerMock, moveMouse(0,3));
  joypadHandler.handleTime();

  joypadHandler.handleAxis(AXIS_RIGHT_VERTICAL, -5*2048);
  EXPECT_CALL(sysConteollerMock, moveMouse(0,-5));
  joypadHandler.handleTime();
}

void JoypadHandlerTestSuite::expectSwitchToLeftDesktop()
{
  EXPECT_CALL(sysConteollerMock, pressKey(30));
  EXPECT_CALL(sysConteollerMock, pressKey(42));
  EXPECT_CALL(sysConteollerMock, pressKey(56));
  EXPECT_CALL(sysConteollerMock, releaseKey(30));
  EXPECT_CALL(sysConteollerMock, releaseKey(42));
  EXPECT_CALL(sysConteollerMock, releaseKey(56));
}

void JoypadHandlerTestSuite::expectSwitchToRightDesktop()
{
  EXPECT_CALL(sysConteollerMock, pressKey(32));
  EXPECT_CALL(sysConteollerMock, pressKey(42));
  EXPECT_CALL(sysConteollerMock, pressKey(56));
  EXPECT_CALL(sysConteollerMock, releaseKey(32));
  EXPECT_CALL(sysConteollerMock, releaseKey(42));
  EXPECT_CALL(sysConteollerMock, releaseKey(56));
}

TEST_F(JoypadHandlerTestSuite, shouldSwitchDesktopToTheLeft_whenLeftAxisGoBelowThreshold)
{
  expectSwitchToLeftDesktop();
  joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, -28667);
}

TEST_F(JoypadHandlerTestSuite, shouldSwitchDesktopToTheRight_whenLeftAxisGoAboveThreshold)
{
  expectSwitchToRightDesktop();
  joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, 28667);
}

TEST_F(JoypadHandlerTestSuite, shouldNotSwitchToDesktopToTheLeft_ifLeftAxisDidntGoAboveThreshold)
{
  expectSwitchToLeftDesktop();
  joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, -28667);
  joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, -28650);
}

TEST_F(JoypadHandlerTestSuite, shouldNotSwitchToDesktopToTheRight_ifLeftAxisDidntGoBelowThreshold)
{
  expectSwitchToRightDesktop();
  joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, 28667);
  joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, 28650);
}

TEST_F(JoypadHandlerTestSuite, shouldAgainSwitchToDesktopToTheLeft_ifLeftAxisGoAboveThreshold)
{
  expectSwitchToLeftDesktop();
  joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, -28667);
  joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, -24667);
  
  expectSwitchToLeftDesktop();
  joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, -28650);
}

TEST_F(JoypadHandlerTestSuite, shouldAgainSwitchToDesktopToTheRight_ifLeftAxisGoBelowThreshold)
{
  expectSwitchToRightDesktop();
  joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, 28667);
  joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, 24667);
  
  expectSwitchToRightDesktop();
  joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, 28650);
}
