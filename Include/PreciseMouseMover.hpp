#pragma once
#include "ISystemController.hpp"
#include "IConfigStore.hpp"

class PreciseMouseMover
{
public:
  PreciseMouseMover(ISystemController& p_sysController,
                    IConfigStore& p_configStore);

  void changeXAxisValues(int);
  void changeYAxisValues(int);
  void changeSlowDown(int);

  void setAxisCoords(int,int,int);
  void handleTime();
private:
  int calculateMovement(int&,int);
  int substractDeadZone(int);
  int calculateSpeedFromAxisPosition(int);
  void recalculateSpeeds();

  ISystemController& sysController;
  IConfigStore& configStore;

  static const int precision=100;
  static const int minSpeed = 20;
  static const int maxSpeed = precision;

  int slowDown;
  int axisX, axisY;
  int speedX, speedY;
  int positionX, positionY;
};

