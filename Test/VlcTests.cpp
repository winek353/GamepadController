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
};

TEST_F(VlcTests, shouldPressSpace_whenButtonX_isPressed)
{
  EXPECT_CALL(sysControllerMock, pressKey(57));
  EXPECT_CALL(sysControllerMock, releaseKey(57));
  
  joypadHandler.handleButton(BUTTON_X, PRESSED);
}
