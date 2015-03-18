#include <gtest/gtest.h>
#include "JoypadHandlerTestBase.hpp"

using namespace testing;

class ClementineShortcutsTestSuite : public JoypadHandlerTestBase
{
public:
  ClementineShortcutsTestSuite() :
    JoypadHandlerTestBase()
  {}
  
  void SetUp()
  {
      EXPECT_CALL(sysControllerMock, getApplicationOnTop()).WillRepeatedly(Return(std::string("clementine")));
      ignoreMouseMovement();
      configStoreDefaultExpectations();
  }
  
  void ignoreMouseMovement()
  {
      EXPECT_CALL(sysControllerMock, moveMouse(_,_)).Times(AnyNumber());
  }
};

TEST_F(ClementineShortcutsTestSuite, shouldPressDownArrow_whenButtonDownIsPressed)
{
  EXPECT_CALL(sysControllerMock, pressKey(108));
  EXPECT_CALL(sysControllerMock, releaseKey(108));
  
  joypadHandler.handleButton(BUTTON_DOWN, PRESSED);
}

TEST_F(ClementineShortcutsTestSuite, shouldPressUpArrow_whenButtonUpIsPressed)
{
  EXPECT_CALL(sysControllerMock, pressKey(103));
  EXPECT_CALL(sysControllerMock, releaseKey(103));
  
  joypadHandler.handleButton(BUTTON_UP, PRESSED);
}

TEST_F(ClementineShortcutsTestSuite, shouldChangeToNextPlaylist_whenButtonRightIsPressed)
{
  EXPECT_CALL(sysControllerMock, pressKey(15));
  EXPECT_CALL(sysControllerMock, releaseKey(15));
  EXPECT_CALL(sysControllerMock, pressKey(29));
  EXPECT_CALL(sysControllerMock, releaseKey(29));

  joypadHandler.handleButton(BUTTON_RIGHT, PRESSED);
}

TEST_F(ClementineShortcutsTestSuite, shouldChangeToPrevoiusPlaylist_whenButtonLeftIsPressed)
{
  EXPECT_CALL(sysControllerMock, pressKey(15));
  EXPECT_CALL(sysControllerMock, releaseKey(15));
  EXPECT_CALL(sysControllerMock, pressKey(29));
  EXPECT_CALL(sysControllerMock, releaseKey(29));
  EXPECT_CALL(sysControllerMock, pressKey(42));
  EXPECT_CALL(sysControllerMock, releaseKey(42));
  
  joypadHandler.handleButton(BUTTON_LEFT, PRESSED);
}

TEST_F(ClementineShortcutsTestSuite, shouldPressEnter_whenButtonX_isPressed)
{
  EXPECT_CALL(sysControllerMock, pressKey(28));
  EXPECT_CALL(sysControllerMock, releaseKey(28));

  joypadHandler.handleButton(BUTTON_X, PRESSED);
}


