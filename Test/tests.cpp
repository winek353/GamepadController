#include <gtest/gtest.h>
#include "JoypadHandlerTestBase.hpp"


using namespace testing;

class JoypadHandlerTestSuite : public JoypadHandlerTestBase
{
public:
  JoypadHandlerTestSuite() :
      JoypadHandlerTestBase()
  {}

  void SetUp()
  {
      EXPECT_CALL(sysControllerMock, getApplicationOnTop()).WillRepeatedly(Return(std::string("plasma-desktop")));
      configStoreDefaultExpectations();
  }

  void expectCtrlAltKey(int keycode)
  {
      EXPECT_CALL(sysControllerMock, pressKey(29));
      EXPECT_CALL(sysControllerMock, releaseKey(29));
      EXPECT_CALL(sysControllerMock, pressKey(56));
      EXPECT_CALL(sysControllerMock, releaseKey(56));
      EXPECT_CALL(sysControllerMock, pressKey(keycode));
      EXPECT_CALL(sysControllerMock, releaseKey(keycode));
  }
};

TEST_F(JoypadHandlerTestSuite, shouldClickLeftMouseButton_whenLBisPressed)
{
  EXPECT_CALL(sysControllerMock, clickMouse(1));
  joypadHandler.handleButton(BUTTON_LB, PRESSED);

  EXPECT_CALL(sysControllerMock, unclickMouse(1));
  joypadHandler.handleButton(BUTTON_LB, RELEASED);
}

TEST_F(JoypadHandlerTestSuite, shouldClickRightMouseButton_whenRBisPressed)
{
  EXPECT_CALL(sysControllerMock, clickMouse(3));
  joypadHandler.handleButton(BUTTON_RB, PRESSED);

  EXPECT_CALL(sysControllerMock, unclickMouse(3));
  joypadHandler.handleButton(BUTTON_RB, RELEASED);
}

TEST_F(JoypadHandlerTestSuite, shouldMoveMouseX_whenAxisRightHorizontalIsMoved)
{
  joypadHandler.handleAxis(AXIS_RIGHT_HORIZONTAL, -3*2048-2048);
  EXPECT_CALL(sysControllerMock, moveMouse(-3,0));
  joypadHandler.handleTime();

  joypadHandler.handleAxis(AXIS_RIGHT_HORIZONTAL, 5*2048+2048);
  EXPECT_CALL(sysControllerMock, moveMouse(5,0));
  joypadHandler.handleTime();
}

TEST_F(JoypadHandlerTestSuite, shouldMoveMouseY_whenAxisRightVertcalIsMoved)
{
  joypadHandler.handleAxis(AXIS_RIGHT_VERTICAL, 3*2048+2048);
  EXPECT_CALL(sysControllerMock, moveMouse(0,3));
  joypadHandler.handleTime();

  joypadHandler.handleAxis(AXIS_RIGHT_VERTICAL, -5*2048-2048);
  EXPECT_CALL(sysControllerMock, moveMouse(0,-5));
  joypadHandler.handleTime();
}

TEST_F(JoypadHandlerTestSuite, shouldNotMoveMouse_whenAxisRightIsInDeadZone)
{
    joypadHandler.handleAxis(AXIS_RIGHT_VERTICAL, 3000);
    EXPECT_CALL(sysControllerMock, moveMouse(0,0));
    joypadHandler.handleTime();

    joypadHandler.handleAxis(AXIS_RIGHT_VERTICAL, -3000);
    EXPECT_CALL(sysControllerMock, moveMouse(0,0));
    joypadHandler.handleTime();
}

TEST_F(JoypadHandlerTestSuite, shouldTurnUpTheVolume_whenLTandY_isPressed)
{
    expectCtrlAltKey(18);
    joypadHandler.handleAxis(AXIS_LT, 29000);
    joypadHandler.handleButton(BUTTON_Y, PRESSED);
}

TEST_F(JoypadHandlerTestSuite, shouldNotTurnUpTheVolume_whenLTandY_isReleased)
{
    joypadHandler.handleAxis(AXIS_LT, 29000);
    joypadHandler.handleButton(BUTTON_Y, RELEASED);
}

TEST_F(JoypadHandlerTestSuite, shuldTurnDownTheVolume_whenLTandA_isPressed)
{
    expectCtrlAltKey(16);
    joypadHandler.handleAxis(AXIS_LT, 29000);
    joypadHandler.handleButton(BUTTON_A, PRESSED);
}

TEST_F(JoypadHandlerTestSuite, shouldPlaySong_whenLTandX_isPressed)
{
    expectCtrlAltKey(17);
    joypadHandler.handleAxis(AXIS_LT, 29000);
    joypadHandler.handleButton(BUTTON_X, PRESSED);
}

TEST_F(JoypadHandlerTestSuite, shouldStopSong_whenLTandB_isPressed)
{
    expectCtrlAltKey(31);
    joypadHandler.handleAxis(AXIS_LT, 29000);
    joypadHandler.handleButton(BUTTON_B, PRESSED);
}

TEST_F(JoypadHandlerTestSuite, shuldNotTurnDownTheVolume_whenLTandA_isReleased)
{
    joypadHandler.handleAxis(AXIS_LT, 29000);
    joypadHandler.handleButton(BUTTON_A, RELEASED);
}

TEST_F(JoypadHandlerTestSuite, shouldNotMoveMouse_whenSteamIsOnTop)
{
    EXPECT_CALL(sysControllerMock, getApplicationOnTop()).WillRepeatedly(Return(std::string("steam")));

    joypadHandler.handleAxis(AXIS_RIGHT_VERTICAL, 3*2048+2048);
    joypadHandler.handleTime();

    joypadHandler.handleAxis(AXIS_RIGHT_VERTICAL, -5*2048-2048);
    joypadHandler.handleTime();
}

TEST_F(JoypadHandlerTestSuite, shouldNotClickMouse_whenSteamIsOnTop)
{
    EXPECT_CALL(sysControllerMock, getApplicationOnTop()).WillRepeatedly(Return(std::string("steam")));

    joypadHandler.handleButton(BUTTON_LB, PRESSED);
    joypadHandler.handleButton(BUTTON_LB, RELEASED);

    joypadHandler.handleButton(BUTTON_RB, PRESSED);
    joypadHandler.handleButton(BUTTON_RB, RELEASED);
}

TEST_F(JoypadHandlerTestSuite, shouldMoveMouseFaster_whenMouseReversedSpeedIsLower)
{
    EXPECT_CALL(configStoreMock, getReversedMouseSpeed()).WillRepeatedly(Return(1024));
    joypadHandler.handleAxis(AXIS_RIGHT_VERTICAL, 6*1024+2048);
    EXPECT_CALL(sysControllerMock, moveMouse(0,6));
    joypadHandler.handleTime();

    joypadHandler.handleAxis(AXIS_RIGHT_VERTICAL, -10*1024-2048);
    EXPECT_CALL(sysControllerMock, moveMouse(0,-10));
    joypadHandler.handleTime();
}

TEST_F(JoypadHandlerTestSuite, shouldNotMoveMouse_whenAxisRightIsInIncreasedDeadZone)
{
    EXPECT_CALL(configStoreMock, getMouseDeadZoneSize()).WillRepeatedly(Return(5500));
    joypadHandler.handleAxis(AXIS_RIGHT_VERTICAL, 5000);
    EXPECT_CALL(sysControllerMock, moveMouse(0,0));
    joypadHandler.handleTime();

    joypadHandler.handleAxis(AXIS_RIGHT_VERTICAL, -5000);
    EXPECT_CALL(sysControllerMock, moveMouse(0,0));
    joypadHandler.handleTime();
}
