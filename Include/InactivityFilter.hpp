

class InactivityFilter
{
public:
    InactivityFilter();

    bool shouldHandleAxis(int axis);
    bool shouldHandleButton(int button);
    void handleTime();
    
    
private:
    void switchToInacticeState();
    void switchToActiveState();

    bool isUserActive;
    
    int timeSinceLastActivity;
    static const int timeToTriggerInactivity = 15*60*100; // 15 min
    
    int buttonsSinceLastInactivity;
    static const int buttonsToTriggerActivity = 30;
};
