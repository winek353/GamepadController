#include "SteamGamesFilter.hpp"

SteamGamesFilter::SteamGamesFilter()
{
    steamGames.insert("steam");
    steamGames.insert("ShadowOfMordor");
}

bool SteamGamesFilter::shouldHandleEvent(std::string appOnTop)
{
    for(const auto& steamGame : steamGames)
        if(steamGame.compare(appOnTop)==0)
            return false;

    return true;
}

