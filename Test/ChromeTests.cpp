#include <gtest/gtest.h>
#include "JoypadHandlerTestBase.hpp"



using namespace testing;

class ChromeTests : public JoypadHandlerTestBase
{
public:
  ChromeTests() :
    JoypadHandlerTestBase()
  {}

  void SetUp()
  {
      EXPECT_CALL(sysControllerMock, getApplicationOnTop()).WillRepeatedly(Return(std::string("chrome")));
      ignoreMouseMovement();
      configStoreDefaultExpectations();
  }

  void ignoreMouseMovement()
  {
      EXPECT_CALL(sysControllerMock, moveMouse(_,_)).Times(AnyNumber());
  }

  void expectCtrlPlusKey(int keycode)
  {
      EXPECT_CALL(sysControllerMock, pressKey(29));
      EXPECT_CALL(sysControllerMock, releaseKey(29));
      EXPECT_CALL(sysControllerMock, pressKey(keycode));
      EXPECT_CALL(sysControllerMock, releaseKey(keycode));
  }

  void expectPressAndReleaseKey(int keycode)
  {
      EXPECT_CALL(sysControllerMock, pressKey(keycode));
      EXPECT_CALL(sysControllerMock, releaseKey(keycode));
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

TEST_F(ChromeTests, shouldOpenNewTab_whenAbuttonIsPressed)
{
    expectCtrlPlusKey(20);

    joypadHandler.handleButton(BUTTON_A, PRESSED);
}

TEST_F(ChromeTests, shouldCloseTab_whenBbuttonIsPressed)
{
    expectCtrlPlusKey(17);

    joypadHandler.handleButton(BUTTON_B, PRESSED);
}

TEST_F(ChromeTests, shouldSwitchToTabToTheLeft_whenLeftButtonIsPressed)
{
    expectCtrlPlusKey(104);

    joypadHandler.handleButton(BUTTON_LEFT, PRESSED);
}

TEST_F(ChromeTests, shouldSwitchToTabToTheRight_whenRightButtonIsPressed)
{
    expectCtrlPlusKey(109);

    joypadHandler.handleButton(BUTTON_RIGHT, PRESSED);
}

TEST_F(ChromeTests, shouldZoomIn_whenUpButtonIsPressed)
{
    expectCtrlPlusKey(13);

    joypadHandler.handleButton(BUTTON_UP, PRESSED);
}

TEST_F(ChromeTests, shouldZoomOut_whenDownButtonIsPressed)
{
    expectCtrlPlusKey(12);

    joypadHandler.handleButton(BUTTON_DOWN, PRESSED);
}

TEST_F(ChromeTests, shouldPressDownArrow_whenAxisLeftVertiacalIsMovedDown)
{
    joypadHandler.handleAxis(AXIS_LEFT_VERTICAL, 32000);

    expectPressAndReleaseKey(108);
    joypadHandler.handleTime();
}

TEST_F(ChromeTests, shouldPressUpArrow_whenAxisLeftVertiacalIsMovedUp)
{
    joypadHandler.handleAxis(AXIS_LEFT_VERTICAL, -32000);

    expectPressAndReleaseKey(103);
    joypadHandler.handleTime();
}

TEST_F(ChromeTests, shouldPressLeftArrow_whenAxisLeftHorizontalIsMovedLeft)
{
    joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, -32000);

    expectPressAndReleaseKey(105);
    joypadHandler.handleTime();
}

TEST_F(ChromeTests, shouldPressRightArrow_whenAxisLeftHorizontalIsMovedRight)
{
    joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, 32000);

    expectPressAndReleaseKey(106);
    joypadHandler.handleTime();
}

TEST_F(ChromeTests, shouldPressRightAndDownArrows_whenLeftJoyIsMovedRightDown)
{
    joypadHandler.handleAxis(AXIS_LEFT_VERTICAL, 32000);
    joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, 32000);

    expectPressAndReleaseKey(108);
    expectPressAndReleaseKey(106);
    joypadHandler.handleTime();
}

TEST_F(ChromeTests, shouldPressDownArrow_everyFourTimesHandleTimeIsCalled)
{
    joypadHandler.handleAxis(AXIS_LEFT_VERTICAL, 32000);

    expectPressAndReleaseKey(108);
    joypadHandler.handleTime();

    for(int i=0;i<3;i++)
        joypadHandler.handleTime();

    expectPressAndReleaseKey(108);
    joypadHandler.handleTime();
}

TEST_F(ChromeTests, shouldPressUpArrow_everyFourTimesHandleTimeIsCalled)
{
    joypadHandler.handleAxis(AXIS_LEFT_VERTICAL, -32000);

    expectPressAndReleaseKey(103);
    joypadHandler.handleTime();

    for(int i=0;i<3;i++)
        joypadHandler.handleTime();

    expectPressAndReleaseKey(103);
    joypadHandler.handleTime();
}

TEST_F(ChromeTests, shouldNotPressAnyArrows_whenLeftJoyIsInDeadZone)
{
    joypadHandler.handleAxis(AXIS_LEFT_VERTICAL, 100);

    joypadHandler.handleTime();
}

TEST_F(ChromeTests, shouldChangeScroolingSpeed_afterLeftJoyUpdate)
{
    joypadHandler.handleAxis(AXIS_LEFT_VERTICAL, 8000);

    expectPressAndReleaseKey(108);
    joypadHandler.handleTime();

    for(int i=0;i<9;i++)
        joypadHandler.handleTime();

    joypadHandler.handleAxis(AXIS_LEFT_VERTICAL, 32000);

    expectPressAndReleaseKey(108);
    joypadHandler.handleTime();
}

TEST_F(ChromeTests, shouldOnlyTurnDownTheVolume_whenLTandA_isPressed)
{
    expectCtrlAltKey(16);
    joypadHandler.handleAxis(AXIS_LT, 29000);
    joypadHandler.handleButton(BUTTON_A, PRESSED);
}
