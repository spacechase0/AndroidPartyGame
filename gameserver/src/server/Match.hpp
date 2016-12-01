#ifndef SERVER_MATCH_HPP
#define SERVER_MATCH_HPP

#include <SFML/System/Mutex.hpp>
#include <SFML/System/Thread.hpp>
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
            ~Match();
            
            void start();
            bool hasStarted() const;
            
            const Client* getHost() const;
            std::vector< Client* > getPlayers() const;
            bool tryToJoin( Client* client );
            void playerLeft( Client* client );
            
            game::MatchData asData() const;
            
            std::string getName() const;
            sf::Uint8 getMaxPlayers() const;
        
        private:
            Server& server;
            
            bool matchStarted = false;
            
            mutable sf::Mutex playersM;
            std::vector< Client* > players;
            
            std::string name;
            sf::Uint8 maxPlayers;
            
            sf::Thread thread;
            void run();
    };
}

#endif // SERVER_MATCH_HPP
