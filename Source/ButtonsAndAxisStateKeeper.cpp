#include "ButtonsAndAxisStateKeeper.hpp"

ButtonsAndAxisStateKeeper::ButtonsAndAxisStateKeeper()
{
    for(int i=0;i<buttonsNumber;i++)
        buttonState[i] = RELEASED;
    
    for(int i=0;i<axisNumber;i++)
        axisState[i] = 0;
}

void ButtonsAndAxisStateKeeper::setButtonState(int buttonIdx, PressedOrReleased pressedOrReleased)
{
    if(buttonIdx < 0 or buttonIdx >= buttonsNumber)
        return;
    
    buttonState[buttonIdx] = pressedOrReleased;
}

PressedOrReleased ButtonsAndAxisStateKeeper::getButtonState(int buttonIdx)
{
    if(buttonIdx < 0 or buttonIdx >= buttonsNumber)
        return RELEASED;
    
    return buttonState[buttonIdx];
}
    
void ButtonsAndAxisStateKeeper::setAxisState(int axisIdx, int value)
{
    if(axisIdx < 0 or axisIdx >= axisNumber)
        return;
        
    axisState[axisIdx] = value;
}

int ButtonsAndAxisStateKeeper::getAxisState(int axisIdx)
{
    if(axisIdx < 0 or axisIdx >= axisNumber)
        return 0;
    
    return axisState[axisIdx];
}
    
    