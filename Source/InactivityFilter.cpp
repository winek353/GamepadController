#include "InactivityFilter.hpp"
#include <iostream>

InactivityFilter::InactivityFilter()
{
    timeSinceLastActivity = 0;
    isUserActive = true;
    
    buttonsSinceLastInactivity = 0;
}

bool InactivityFilter::shouldHandleAxis(int axis)
{
    buttonsSinceLastInactivity++;
    if(buttonsSinceLastInactivity > buttonsToTriggerActivity)
        switchToActiveState();
    
    return isUserActive;
}

bool InactivityFilter::shouldHandleButton(int button)
{
    buttonsSinceLastInactivity++;
    if(buttonsSinceLastInactivity > buttonsToTriggerActivity)
        switchToActiveState();

    return isUserActive;
}

void InactivityFilter::switchToInacticeState()
{
    isUserActive = false;
    
    buttonsSinceLastInactivity = 0;
    
    std::cout << "Switch to inactive state!\n";
}

void InactivityFilter::switchToActiveState()
{
    isUserActive = true;
    
    timeSinceLastActivity = 0;
}

void InactivityFilter::handleTime()
{
    timeSinceLastActivity++;
    
    if(isUserActive and timeSinceLastActivity > timeToTriggerInactivity)
       switchToInacticeState(); 
}
