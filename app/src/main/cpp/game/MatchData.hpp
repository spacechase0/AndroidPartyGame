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
            MatchData( const std::string& theName, sf::Uint8 thePlayers );
            
            std::string name = "Match";
            sf::Uint8 maxPlayers = 4;
            std::vector< std::string > players;
    };
}

#endif // GAME_MATCHDATA_HPP
