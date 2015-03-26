#include <gtest/gtest.h>
#include "JoypadHandlerTestBase.hpp"

class DolphinTests : public JoypadHandlerTestBase
{
public:
  DolphinTests() :
    JoypadHandlerTestBase()
  {}

  void SetUp()
  {
      EXPECT_CALL(sysControllerMock, getApplicationOnTop()).WillRepeatedly(Return(std::string("dolphin")));
      ignoreMouseMovement();
      configStoreDefaultExpectations();
  }

};

TEST_F(DolphinTests, shouldPressEnter_whenButtonA_isPressed)
{
  EXPECT_CALL(sysControllerMock, pressKey(28));

  joypadHandler.handleButton(BUTTON_A, PRESSED);
}

TEST_F(DolphinTests, shouldPressBackspace_whenButtonB_isPressed)
{
  EXPECT_CALL(sysControllerMock, pressKey(14));

  joypadHandler.handleButton(BUTTON_B, PRESSED);
}

TEST_F(DolphinTests, shouldPressLeftArrow_whenButtolLeftIsPressed)
{
  EXPECT_CALL(sysControllerMock, pressKey(105));

  joypadHandler.handleButton(BUTTON_LEFT, PRESSED);
}

TEST_F(DolphinTests, shouldReleaseLeftArrow_whenButtonLeftIsReleased)
{
  EXPECT_CALL(sysControllerMock, releaseKey(105));
  
  joypadHandler.handleButton(BUTTON_LEFT, RELEASED);
}

TEST_F(DolphinTests, shouldPressRightArrow_whenButtolRightIsPressed)
{
  EXPECT_CALL(sysControllerMock, pressKey(106));

  joypadHandler.handleButton(BUTTON_RIGHT, PRESSED);
}

TEST_F(DolphinTests, shouldReleaseRightArrow_whenButtonRightIsReleased)
{
  EXPECT_CALL(sysControllerMock, releaseKey(106));
  
  joypadHandler.handleButton(BUTTON_RIGHT, RELEASED);
}

TEST_F(DolphinTests, shouldPressUpArrow_whenButtonUpIsPressed)
{
  EXPECT_CALL(sysControllerMock, pressKey(103));

  joypadHandler.handleButton(BUTTON_UP, PRESSED);
}

TEST_F(DolphinTests, shouldReleaseUpArrow_whenButtonUpIsReleased)
{
  EXPECT_CALL(sysControllerMock, releaseKey(103));
  
  joypadHandler.handleButton(BUTTON_UP, RELEASED);
}

TEST_F(DolphinTests, shouldPressiDownArrow_whenButtonDownIsPressed)
{
  EXPECT_CALL(sysControllerMock, pressKey(108));

  joypadHandler.handleButton(BUTTON_DOWN, PRESSED);
}

TEST_F(DolphinTests, shouldReleaseDownArrow_whenButtonDownIsReleased)
{
  EXPECT_CALL(sysControllerMock, releaseKey(108));
  
  joypadHandler.handleButton(BUTTON_DOWN, RELEASED);
}
