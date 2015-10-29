#include "ApplicationShortcutsBase.hpp"


ApplicationShortcutsBase::ApplicationShortcutsBase(ISystemController* p_sysController,
                                                   IConfigStore* p_configStore,
                                                   IKeyPresser& p_keyPresser) :
    sysController(p_sysController),
    configStore(p_configStore),
    keyPresser(p_keyPresser),
    arrowsToArrowsPresser(p_keyPresser),
    mouseScrooler(*configStore, *p_sysController),
    preciseMouseMover(*p_sysController, *p_configStore)
{
}
