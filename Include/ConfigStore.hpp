#pragma once
#include "IConfigStore.hpp"

class ConfigStore : public IConfigStore
{
public:
    virtual int getReversedMouseSpeed();
    virtual int getMouseDeadZoneSize();
};
