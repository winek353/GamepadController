#pragma once
#include <QObject>
#include <QSocketNotifier>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/joystick.h>
#include <QSocketNotifier>
#include <QDir>
#include <QTimer>
#include "JoypadHandler.hpp"

using namespace std;

class JoypadListener : public QObject
{
  Q_OBJECT
public:
  JoypadListener();
  
  QSocketNotifier *joydevFileHandle;
public slots:
  void handleJoyEvents(int fd);
  void timerCalled();
  
private:
  int dev;
  JoypadHandler* handler;
  QTimer *timer;
  
  void handleButton(int,int);
  void handleAxis(int,int);
};
