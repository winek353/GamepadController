#include <QX11Info>
#include <X11/keysymdef.h>
#include <stdlib.h>
#include <fstream>
#include "SystemController.hpp"
#include <iostream>
#include <ctime>


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

std::string getCmdOutput(const std::string& mStr)
{
    std::string result, file;
    FILE* pipe = popen(mStr.c_str(), "r");
    char buffer[256];

    while(fgets(buffer, sizeof(buffer), pipe) != NULL)
    {
        file = buffer;
        result += file.substr(0, file.size() - 1);
    }

    pclose(pipe);
    return result;
}

std::string SystemController::getApplicationOnTop()
{
    static std::string appOnTop;
    static int lastTimeCalled = std::clock();
    int timeNow = std::clock();
    if(timeNow - lastTimeCalled > CLOCKS_PER_SEC/50)
    {
        std::string command = "cat /proc/$(xdotool getwindowpid $(xdotool getwindowfocus))/comm";
        lastTimeCalled = std::clock();
        appOnTop = getCmdOutput(command);
    }

    return appOnTop;
}
