#pragma once
#include <string>
#include <X11/extensions/XTest.h>
#include "ISystemController.hpp"
#include "IProcessesNamesSaver.hpp"

class SystemController : public ISystemController
{
public:
  SystemController(IProcessesNamesSaver&);
  void pressKey(int);
  void releaseKey(int);
  void moveMouse(int, int);
  void clickMouse(int);
  void unclickMouse(int);
  void runCommand(std::string);
  std::string getApplicationOnTop();
  
private:
    Display* display;
    IProcessesNamesSaver& processesNamesSaver;
};
