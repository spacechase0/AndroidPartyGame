#include "game/MatchData.hpp"

namespace game
{
    MatchData::MatchData()
    {
    }
    
    MatchData::MatchData( const std::string& theName, sf::Uint8 thePlayers )
    :   name( theName ),
        maxPlayers( thePlayers )
    {
    }
}
