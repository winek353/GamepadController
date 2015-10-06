#pragma once
#include "PressedOrReleased.hpp"

class ButtonsAndAxisStateKeeper
{
public:
    ButtonsAndAxisStateKeeper();
    
    void setButtonState(int, PressedOrReleased);
    PressedOrReleased getButtonState(int);
    
    void setAxisState(int, int);
    int getAxisState(int);
    
private:
    static const int axisNumber = 6;
    int axisState[axisNumber];
    
    static const int buttonsNumber = 15;
    PressedOrReleased buttonState[buttonsNumber];
};
