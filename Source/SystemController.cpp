#include <QX11Info>
#include <X11/keysymdef.h>
#include <stdlib.h>
#include "SystemController.hpp"


SystemController::SystemController()
{
  display = QX11Info::display();
}

void SystemController::pressKey(int key)
{
  XTestFakeKeyEvent(display, 8+key, 1, 0);
}

void SystemController::releaseKey(int key)
{
  XTestFakeKeyEvent(display, 8+key, 0, 0);
}

void SystemController::moveMouse(int x, int y)
{
  XTestFakeRelativeMotionEvent(display, x, y, 0);
}

void SystemController::runCommand(std::string command)
{
  system(command.c_str());
}

void SystemController::clickMouse(int button)
{
  XTestFakeButtonEvent(display, button, 1, 0);
}

void SystemController::unclickMouse(int button)
{
  XTestFakeButtonEvent(display, button, 0, 0);
}

std::string SystemController::getApplicationOnTop()
{
    return "plasma-desktop";
}
