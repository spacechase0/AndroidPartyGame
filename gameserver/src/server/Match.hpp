#ifndef SERVER_MATCH_HPP
#define SERVER_MATCH_HPP

#include <SFML/System/Clock.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Thread.hpp>
#include <string>
#include <vector>

namespace game
{
    class MatchData;
    class PlayerData;
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
            
            void playerRolledDie( Client* client );
            
            game::MatchData asData() const;
            
            std::string getName() const;
            std::string getMapId() const;
            sf::Uint8 getMaxPlayers() const;
        
        private:
            Server& server;
            
            bool matchStarted = false;
            
            mutable sf::Mutex playersM;
            std::vector< Client* > players;
            
            std::string name;
            std::string mapId;
            sf::Uint8 maxPlayers;
            
            sf::Thread thread;
            void run();
            void update();
            
            int currentTurn = 0;
            sf::Uint8 roll = 0xFF;
            sf::Clock lastMove;
            sf::Clock lastRoll;
            
            std::vector< game::PlayerData > playerData;
            
            friend class Server;
    };
}

#endif // SERVER_MATCH_HPP
