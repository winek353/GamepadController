#include "JoypadHandler.hpp"
#include <iostream>
#include "Logger.hpp"
#include "IConfigStore.hpp"
#include "ClementineShortcuts.hpp"


using namespace std;

JoypadHandler::JoypadHandler(ISystemController* p_systemController,
                             IConfigStore* p_configStore) :
    systemController(p_systemController),
    configStore(p_configStore),
    mouseMover(*p_systemController, *p_configStore),
    keyPresser(*p_systemController)
{
	flag = true;
    isLT_pressed = false;
    
    applicationShortcuts[0] = new DolphinShortcuts(p_systemController);
    applicationShortcuts[1] = new ChromeShortcuts(p_systemController, configStore, keyPresser);
    applicationShortcuts[2] = new ClementineShortcuts(p_systemController);
    applicationShortcuts[3] = new VlcShortcuts(p_systemController, configStore);
}

JoypadHandler::~JoypadHandler()
{
  for(int i=0;i<applicationShortcutsSize;i++)
    delete applicationShortcuts[i];
}

bool isLT_belowThreshold (int value, IConfigStore* configStore)
    {
        if(value>= configStore->getLtPressedThreshold())
        {
             return true;
        }
        else
        {
            return false;
        }
    }
void JoypadHandler::pressCtrlPlusAltPlusKey(int key)
{
    systemController->pressKey(29);
    systemController->pressKey(56);
    systemController->pressKey(key);
    systemController->releaseKey(key);
    systemController->releaseKey(56);
    systemController->releaseKey(29);
}

void JoypadHandler::handleButton(JoypadButton button, PressedOrReleased pressedOrReleased)
{
  DEBUG << "Button " << button << " was " << pressedOrReleased;
if(systemController->getApplicationOnTop().compare("steam")!=0)
    {
	string appOnTop = systemController->getApplicationOnTop();

	for(int i=0;i<applicationShortcutsSize; i++)
	{
	  if(appOnTop.compare(applicationShortcuts[i]->getApplication())==0)
	  {
	    applicationShortcuts[i]->handleButton(button, pressedOrReleased, isLT_pressed);
	    break;
	  }
	}  
	    
	    if(button==BUTTON_XBOX)
	    {
		if(pressedOrReleased == PRESSED)
		    systemController->runCommand("~/bin/GamepadController/applaunch.sh");
	    }
	    
	    if(button == BUTTON_LB)
	    {
		  if(pressedOrReleased == PRESSED)
			  systemController->clickMouse(1);
		  else
			  systemController->unclickMouse(1);
	    }
	      if(button == BUTTON_RB)
	    {
		  if(pressedOrReleased == PRESSED)
			  systemController->clickMouse(3);
		  else
			  systemController->unclickMouse(3);
	    }
    }
  if (button == BUTTON_X && isLT_pressed && pressedOrReleased == PRESSED)
  {
	pressCtrlPlusAltPlusKey(17);
  }
  if (button == BUTTON_B && isLT_pressed && pressedOrReleased == PRESSED)
  {
	pressCtrlPlusAltPlusKey(31);
  }
  if  (button == BUTTON_Y && isLT_pressed && pressedOrReleased == PRESSED)
  {
      pressCtrlPlusAltPlusKey(18);
  }
    if (button == BUTTON_A && isLT_pressed && pressedOrReleased == PRESSED)
  {
      pressCtrlPlusAltPlusKey(16);
  }
}

void JoypadHandler::handleAxis(JoypadAxis axis, int value)
{
  DEBUG << "Axis " << axis << " value = " << value;
      if(systemController->getApplicationOnTop().compare("steam")!=0)
    {
      string appOnTop = systemController->getApplicationOnTop();

      for(int i=0;i<applicationShortcutsSize;i++)
      {
	if(appOnTop.compare(applicationShortcuts[i]->getApplication())==0)
	{
	  applicationShortcuts[i]->handleAxis(axis, value);
	  break;
	}
      }
      
          if(axis==AXIS_RIGHT_HORIZONTAL)
          {
              mouseMover.changeXAxisValues(value);
          }
          else if(axis == AXIS_RIGHT_VERTICAL)
          {
              mouseMover.changeYAxisValues(value);
          }
      }
   if (axis ==AXIS_LT)
   {
       isLT_pressed = isLT_belowThreshold (value, configStore);
   }
   if ((axis ==AXIS_LEFT_HORIZONTAL) && isLT_pressed)
   {
       if (value >(-configStore->getSwitchDesktopLowerThreshold()) &&
           value<configStore->getSwitchDesktopLowerThreshold()) 
           flag =true; // isLeftHorizontalAxisInMiddle
       if ( (value<(-configStore->getSwitchDesktopHigherThreshold()) && flag)  ||
            (value>configStore->getSwitchDesktopHigherThreshold() && flag))
       {
           LeftAxisHorizontalMovements (value, flag);
       }	
   }
}

void JoypadHandler::handleTime() // once a 1/20 s
{
    DEBUG << "handleTime was called";
    if(systemController->getApplicationOnTop().compare("steam")!=0)
    {
        mouseMover.moveMouse();
      string appOnTop = systemController->getApplicationOnTop();

      for(int i=0;i<applicationShortcutsSize;i++)
      {
	if(appOnTop.compare(applicationShortcuts[i]->getApplication())==0)
	{
	  applicationShortcuts[i]->handleTime();
	  break;
	}
      }
    }
}
void JoypadHandler::LeftAxisHorizontalMovements (int value, bool &flag)
	{
		if (value<(-configStore->getSwitchDesktopHigherThreshold()))
		{
			systemController->pressKey(42); // switchToDesktopToTheLeft
			systemController->pressKey(56);
			systemController->pressKey(30);
			systemController->releaseKey(30);
			systemController->releaseKey(56);
			systemController->releaseKey(42);
		}
        else if(value>configStore->getSwitchDesktopHigherThreshold())
		{
			systemController->pressKey(42); //
			systemController->pressKey(56);
			systemController->pressKey(32);
			systemController->releaseKey(32);
			systemController->releaseKey(56);
			systemController->releaseKey(42);
		}
		flag=false;
	}
