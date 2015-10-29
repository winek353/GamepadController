#include "PreciseMouseMover.hpp"
#include <iostream>
using namespace std;

PreciseMouseMover::PreciseMouseMover(ISystemController& p_sysController,
                                     IConfigStore& p_configStore) :
  sysController(p_sysController),
  configStore(p_configStore)
{
  slowDown = precision;
  axisX = axisY = 0;
  speedX = speedY = 0;
  positionX = positionY = 0;
}

void PreciseMouseMover::changeXAxisValues(int x)
{
  axisX = x;
  recalculateSpeeds();
}

void PreciseMouseMover::changeYAxisValues(int y)
{
  axisY = y;
  recalculateSpeeds();
}

void PreciseMouseMover::recalculateSpeeds()
{
  speedX = calculateSpeedFromAxisPosition(axisX);
  speedY = calculateSpeedFromAxisPosition(axisY);
}

void PreciseMouseMover::changeSlowDown(int value)
{
  slowDown = maxSpeed - (((value + (1<<15)) * (maxSpeed - minSpeed)) >> 16);
  recalculateSpeeds();
}

void PreciseMouseMover::handleTime()
{
  int moveX = calculateMovement(positionX, speedX);
  int moveY = calculateMovement(positionY, speedY);
  
  sysController.moveMouse(moveX, moveY);
}

int PreciseMouseMover::calculateMovement(int& position,int speed)
{
  position += speed;

  int movement = position / precision;
  position = position % precision;

  return movement;

}

int PreciseMouseMover::substractDeadZone(int value)
{
    if (value >= configStore.getMouseDeadZoneSize())
        return (value - configStore.getMouseDeadZoneSize());
    else if(value <= -configStore.getMouseDeadZoneSize())
        return (value + configStore.getMouseDeadZoneSize());
    else return 0;
}


int PreciseMouseMover::calculateSpeedFromAxisPosition(int axisValue)
{
    return substractDeadZone(axisValue) * slowDown
//precision 
     / configStore.getReversedMouseSpeed();
}
