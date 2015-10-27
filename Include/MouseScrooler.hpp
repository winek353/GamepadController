#pragma once
#include "IConfigStore.hpp"
#include "ISystemController.hpp"

class MouseScrooler
{
public:
  MouseScrooler(IConfigStore&, ISystemController&);
  
  void setAxisValue(int);
  void handleTime();
private:
  int frequency;
  int eventCounter;
  bool moveOrNot;
  
  IConfigStore& configStore;
  ISystemController& sysController;
};
