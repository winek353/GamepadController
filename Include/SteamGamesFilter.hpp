#pragma once
#include <string>
#include <set>

class SteamGamesFilter
{
public:
    SteamGamesFilter();

    bool shouldHandleEvent(std::string);
    
private:
    std::set<std::string> steamGames;
};

