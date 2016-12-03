#include "game/MatchData.hpp"

namespace game
{
    MatchData::MatchData()
    {
    }
    
    MatchData::MatchData( const std::string& theName, const std::string& theMap, sf::Uint8 thePlayers )
    :   name( theName ),
        map( theMap ),
        maxPlayers( thePlayers )
    {
    }
}
