#pragma once
#include "IApplicationShortcuts.hpp"

class ISystemController;
class IConfigStore;
class IKeyPresser;

class ApplicationShortcutsBase : public IApplicationShortcuts
{
protected:
    ApplicationShortcutsBase(ISystemController* sysController,
                             IConfigStore* configStore,
                             IKeyPresser& keyPresser);

    ISystemController* sysController;
    IConfigStore* configStore;
    IKeyPresser& keyPresser;
};
