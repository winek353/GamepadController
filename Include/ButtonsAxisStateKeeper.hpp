#include "PressedOrReleased.hpp"

class ButtonsAndAxisStateKeeper
{
public:
    void setButtonState(int, PressedOrReleased);
    PressedOrReleased getButtonState(int);
    
    void setAxisState(int, int);
    int getAxisState(int);
};
