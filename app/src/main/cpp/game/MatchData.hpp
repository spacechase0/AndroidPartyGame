#ifndef GAME_MATCHDATA_HPP
#define GAME_MATCHDATA_HPP

#include <string>
#include <vector>

namespace game
{
    class MatchData
    {
        public:
            MatchData();
            MatchData( const std::string& theName, const std::string& theMap, sf::Uint8 thePlayers );
            
            std::string name = "Match";
            std::string map = "test";
            sf::Uint8 maxPlayers = 4;
            std::vector< std::string > players;
    };
}

#endif // GAME_MATCHDATA_HPP
