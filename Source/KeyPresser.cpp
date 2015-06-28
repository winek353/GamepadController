#include "KeyPresser.hpp"

KeyPresser::KeyPresser(ISystemController& p_sysController) :
    sysController(p_sysController)
{
}

void KeyPresser::pressKey(int keyCode)
{
    if (not isKeyInRange(keyCode))
        return;

    sysController.pressKey(keyCode);
    isKeyPressed[keyCode] = true;
}

bool KeyPresser::isKeyInRange(int keyCode)
{
    return keyCode >= 0 && keyCode < maxKeyNumber;
}

void KeyPresser::releaseKey(int keyCode)
{
    if (not isKeyInRange(keyCode))
        return;

    sysController.releaseKey(keyCode);
    isKeyPressed[keyCode] = false;
}

void KeyPresser::pressAndReleaseKey(int keyCode)
{
    if (not isKeyInRange(keyCode))
        return;

    sysController.pressKey(keyCode);
    sysController.releaseKey(keyCode);
    isKeyPressed[keyCode] = false;
}

void KeyPresser::releaseAll()
{
    for (int i=0;i<maxKeyNumber;i++)
        if (isKeyPressed[i])
        {
            sysController.releaseKey(i);
        }
}


void KeyPresser::pressCtrlPlusKey(int keyCode)
{
    pressKey(29);
    pressAndReleaseKey(keyCode);
    releaseKey(29);
}
