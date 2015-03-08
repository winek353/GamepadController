#pragma once

class IConfigStore
{
public:
    virtual int getReversedMouseSpeed() = 0;
    virtual int getMouseDeadZoneSize() = 0;
};
