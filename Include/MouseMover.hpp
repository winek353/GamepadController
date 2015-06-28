#pragma once
#include "ISystemController.hpp"
#include "IConfigStore.hpp"

class MouseMover
{
public:
    MouseMover(ISystemController&,
               IConfigStore&);

    void moveMouse();
    void changeXAxisValues(int);
    void changeYAxisValues(int);
private:
    int calculateSpeedFromAxisPosition(int);

    int speedX, speedY;
    ISystemController& sysController;
    IConfigStore& configStore;
};

