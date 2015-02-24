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

  void SetUp()
  {
      EXPECT_CALL(sysConteollerMock, getApplicationOnTop()).WillRepeatedly(Return(std::string("plasma-desktop")));
  }

protected:
  StrictMock<SystemControllerMock> sysConteollerMock;
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
  joypadHandler.handleAxis(AXIS_RIGHT_HORIZONTAL, -3*2048-2048);
  EXPECT_CALL(sysConteollerMock, moveMouse(-3,0));
  joypadHandler.handleTime();

  joypadHandler.handleAxis(AXIS_RIGHT_HORIZONTAL, 5*2048+2048);
  EXPECT_CALL(sysConteollerMock, moveMouse(5,0));
  joypadHandler.handleTime();
}

TEST_F(JoypadHandlerTestSuite, shouldMoveMouseY_whenAxisRightVertcalIsMoved)
{
  joypadHandler.handleAxis(AXIS_RIGHT_VERTICAL, 3*2048+2048);
  EXPECT_CALL(sysConteollerMock, moveMouse(0,3));
  joypadHandler.handleTime();

  joypadHandler.handleAxis(AXIS_RIGHT_VERTICAL, -5*2048-2048);
  EXPECT_CALL(sysConteollerMock, moveMouse(0,-5));
  joypadHandler.handleTime();
}

TEST_F(JoypadHandlerTestSuite, shouldNotMoveMouse_whenAxisRightIsInDeadZone)
{
    joypadHandler.handleAxis(AXIS_RIGHT_VERTICAL, 3000);
    EXPECT_CALL(sysConteollerMock, moveMouse(0,0));
    joypadHandler.handleTime();

    joypadHandler.handleAxis(AXIS_RIGHT_VERTICAL, -3000);
    EXPECT_CALL(sysConteollerMock, moveMouse(0,0));
    joypadHandler.handleTime();
}



