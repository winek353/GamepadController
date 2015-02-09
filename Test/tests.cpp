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

TEST_F(JoypadHandlerTestSuite, no_test)
{
}
