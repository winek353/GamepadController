#pragma once
#include "ISystemController.hpp"
#include "JoypadButton.hpp"
#include "PressedOrReleased.hpp"
#include "JoypadAxis.hpp"
#include "IConfigStore.hpp"
#include "ApplicationShortcutsBase.hpp"

class KtorrentShortcuts : public ApplicationShortcutsBase
{
public:
    KtorrentShortcuts(ISystemController*,
                      IConfigStore*,
                      IKeyPresser&);

    string getApplication();
    void handleButton(JoypadButton button, PressedOrReleased pressedOrReleased, bool isLT_belowThreshold);
    void handleAxis(JoypadAxis axis, int value, bool isLT_belowThreshold);
    void handleTime();
private:
};