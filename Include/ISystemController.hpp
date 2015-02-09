#pragma once
#include <string>

class ISystemController
{
public:
  virtual void pressKey(int) = 0;
  virtual void releaseKey(int) = 0;
  virtual void moveMouse(int, int) = 0;
  virtual void clickMouse(int) = 0;
  virtual void unclickMouse(int) = 0;
  virtual void runCommand(std::string command) = 0;
};
