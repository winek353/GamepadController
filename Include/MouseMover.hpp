#pragma once
#include "ISystemController.hpp"
#include "IConfigStore.hpp"
#include "ButtonsAndAxisStateKeeper.hpp"

class MouseMover
{
public:
    MouseMover(ISystemController&,
               IConfigStore&,
               ButtonsAndAxisStateKeeper&);

    void moveMouse();
    void changeXAxisValues(int);
    void changeYAxisValues(int);
private:
    int calculateSpeedFromAxisPosition(int);

    int speedX, speedY;
    
    int moveX, moveY;
    
    ISystemController& sysController;
    IConfigStore& configStore;
    ButtonsAndAxisStateKeeper& stateKeeper;
};

