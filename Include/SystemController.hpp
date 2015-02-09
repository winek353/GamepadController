#pragma once
#include <string>
#include <X11/extensions/XTest.h>
#include "ISystemController.hpp"

class SystemController : public ISystemController
{
public:
  SystemController();
  void pressKey(int);
  void releaseKey(int);
  void moveMouse(int, int);
  void clickMouse(int);
  void unclickMouse(int);
  void runCommand(std::string);
  
private:
  Display* display;
};
