#ifndef SERVER_MATCH_HPP
#define SERVER_MATCH_HPP

#include <string>
#include <vector>

namespace game
{
    class MatchData;
}

namespace server
{
    class Client;
    class Server;
    
    class Match
    {
        public:
            Match( Server& theServer, const game::MatchData& data, Client* host );
            
            const Client* getHost() const;
            const std::vector< Client* > getPlayers() const;
            
            game::MatchData asData() const;
            
            std::string getName() const;
            sf::Uint8 getMaxPlayers() const;
        
        private:
            Server& server;
            std::vector< Client* > players;
            
            std::string name;
            sf::Uint8 maxPlayers;
    };
}

#endif // SERVER_MATCH_HPP
