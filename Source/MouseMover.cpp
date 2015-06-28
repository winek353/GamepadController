#include "MouseMover.hpp"

MouseMover::MouseMover(ISystemController& p_sysController,
                       IConfigStore& p_configStore) :
    sysController(p_sysController),
    configStore(p_configStore)
{
    speedX = speedY = 0;
}

void MouseMover::moveMouse()
{
    sysController.moveMouse(speedX,speedY);
}

void MouseMover::changeXAxisValues(int axisValue)
{
    speedX = calculateSpeedFromAxisPosition(axisValue);
}

void MouseMover::changeYAxisValues(int axisValue)
{
    speedY = calculateSpeedFromAxisPosition(axisValue);
}

int MouseMover::calculateSpeedFromAxisPosition(int axisValue)
{
    if (axisValue >= configStore.getMouseDeadZoneSize())
        return (axisValue - configStore.getMouseDeadZoneSize()) / configStore.getReversedMouseSpeed();
    else if(axisValue <= -configStore.getMouseDeadZoneSize())
        return (axisValue + configStore.getMouseDeadZoneSize()) / configStore.getReversedMouseSpeed();
    else return 0;
}

