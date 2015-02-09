#pragma once
#include "ISystemController.hpp"
#include <gmock/gmock.h>

class SystemControllerMock : public ISystemController
{
public:
  MOCK_METHOD1(pressKey, void(int));
  MOCK_METHOD1(releaseKey, void(int));
  MOCK_METHOD2(moveMouse, void(int, int));
  MOCK_METHOD1(clickMouse, void(int));
  MOCK_METHOD1(unclickMouse, void(int));

  MOCK_METHOD1(runCommand, void(std::string command));
};
