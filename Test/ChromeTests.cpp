#include <gtest/gtest.h>
#include "SystemControllerMock.hpp"
#include "JoypadHandler.hpp"

using namespace testing;

class ChromeTests : public Test
{
public:
  ChromeTests() :
    sysControllerMock(),
    joypadHandler(&sysControllerMock)
  {}

  void SetUp()
  {
      EXPECT_CALL(sysControllerMock, getApplicationOnTop()).WillRepeatedly(Return(std::string("chrome")));
  }

  void expectCtrlPlusKey(int keycode)
  {
      EXPECT_CALL(sysControllerMock, pressKey(29));
      EXPECT_CALL(sysControllerMock, releaseKey(29));
      EXPECT_CALL(sysControllerMock, pressKey(keycode));
      EXPECT_CALL(sysControllerMock, releaseKey(keycode));
  }

protected:
  StrictMock<SystemControllerMock> sysControllerMock;
  JoypadHandler joypadHandler;
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
