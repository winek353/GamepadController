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