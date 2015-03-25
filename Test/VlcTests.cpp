#include <gtest/gtest.h>
#include "JoypadHandlerTestBase.hpp"

using namespace testing;

class VlcTests : public JoypadHandlerTestBase
{
public:
  VlcTests() :
    JoypadHandlerTestBase()
  {}
  
  void SetUp()
  {
      EXPECT_CALL(sysControllerMock, getApplicationOnTop()).WillRepeatedly(Return(std::string("vlc")));
      ignoreMouseMovement();
      configStoreDefaultExpectations();
  }
  
  void moveToSlowForwardInterval()
  {
      EXPECT_CALL(sysControllerMock, pressKey(42));
      EXPECT_CALL(sysControllerMock, pressKey(106));
      
      joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, 6666);
  }
};

TEST_F(VlcTests, shouldPressSpace_whenButtonX_isPressed)
{
  EXPECT_CALL(sysControllerMock, pressKey(57));
  EXPECT_CALL(sysControllerMock, releaseKey(57));
  
  joypadHandler.handleButton(BUTTON_X, PRESSED);
}

TEST_F(VlcTests, shouldPressS_whenButtonB_isPressed)
{
  EXPECT_CALL(sysControllerMock, pressKey(31));
  EXPECT_CALL(sysControllerMock, releaseKey(31));
  
  joypadHandler.handleButton(BUTTON_B, PRESSED);
}

TEST_F(VlcTests, shouldPressF_whenButtonStart_isPressed)
{
  EXPECT_CALL(sysControllerMock, pressKey(33));
  EXPECT_CALL(sysControllerMock, releaseKey(33));
  
  joypadHandler.handleButton(BUTTON_START, PRESSED);
}

TEST_F(VlcTests, shouldScroolForwardSlowly_whenAxisLeftHorizontal_isAboveVlcSlowScroolThreshold)
{
  moveToSlowForwardInterval();
}

TEST_F(VlcTests, shouldDoNothing_whenAxisLeftHorizontalStaysInDeadZone)
{
  joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, 5666);
}

TEST_F(VlcTests, shouldScroolBackwardSlowly_whenAxisLeftHorizontal_isBelowMinusVlcSlowScroolThreshold)
{
  EXPECT_CALL(sysControllerMock, pressKey(42));
  EXPECT_CALL(sysControllerMock, pressKey(105));
  
  joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, -6666);
}

TEST_F(VlcTests, shouldStopScrooling_whenAxisLeftHorizontalReturnsToDeadZone)
{
  EXPECT_CALL(sysControllerMock, pressKey(42));
  EXPECT_CALL(sysControllerMock, pressKey(105));
  
  joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, -6666);
  
  EXPECT_CALL(sysControllerMock, releaseKey(42));
  EXPECT_CALL(sysControllerMock, releaseKey(105));
  
  joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, 222);
}

TEST_F(VlcTests, shouldDoNothing_whenAxisLeftHorizontalStaysInSlowForwardInterval)
{
  moveToSlowForwardInterval();
  joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, 7666);
}

TEST_F(VlcTests, shouldStopSlowScrooling_andStartMediumScrooling_whenAxisLeftHorizontal_movesFromSlowToMediumForwardInterval)
{
  moveToSlowForwardInterval();
  
  EXPECT_CALL(sysControllerMock, releaseKey(42));
  EXPECT_CALL(sysControllerMock, releaseKey(106));
  EXPECT_CALL(sysControllerMock, pressKey(56));
  EXPECT_CALL(sysControllerMock, pressKey(106));
  
  joypadHandler.handleAxis(AXIS_LEFT_HORIZONTAL, 13666);
}
