#pragma once

class IKeyPresser
{
public:
    virtual void pressKey(int keyCode) = 0;
    virtual void releaseKey(int keyCode) = 0;
    virtual void pressAndReleaseKey(int keyCode) = 0;
    virtual void pressCtrlPlusKey(int keyCode) = 0;
    virtual void releaseAll() = 0;
};
