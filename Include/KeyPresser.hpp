#pragma once
#include "IKeyPresser.hpp"
#include "ISystemController.hpp"

class KeyPresser : public IKeyPresser
{
public:
    KeyPresser(ISystemController&);
    void pressKey(int keyCode);
    void releaseKey(int keyCode);
    void pressCtrlPlusKey(int keyCode);
    void pressAndReleaseKey(int keyCode);
    void releaseAll();
private:
    static const int maxKeyNumber = 256;
    bool isKeyPressed[maxKeyNumber];
    bool isKeyInRange(int);

    ISystemController& sysController;
};
