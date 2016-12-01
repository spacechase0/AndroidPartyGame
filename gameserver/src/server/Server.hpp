#ifndef SERVER_SERVER_HPP
#define SERVER_SERVER_HPP

#include <list>
#include <set>
#include <SFML/Network/TcpListener.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Thread.hpp>
#include <util/Logger.hpp>

#include "server/Lobby.hpp"

namespace game
{
    class MatchData;
}

namespace server
{
    class Client;
    class IUserDatabase;
    class Match;
    
    class Server
    {
        public:
            Server();
            ~Server();
            
            util::Logger log;
            std::unique_ptr< IUserDatabase > users;
            void addMatch( std::unique_ptr< Match > match );
            void removeMatch( Match* match );
            Match* findMatch( const std::string& host );
            std::vector< game::MatchData > getMatchData() const;
            
            void run();
            void stop();
            inline bool isRunning() const { return running; }
        
        private:
            bool running = true;
            
            mutable sf::Mutex clientsM;
            std::list< std::unique_ptr< Client > > clients;
            
            sf::Thread lobbyThread;
            Lobby lobby;
            void runLobby();
            
            mutable sf::Mutex matchesM;
            std::set< std::unique_ptr< Match > > matches;
            
            sf::Thread listenerThread;
            sf::TcpListener listener;
            void listen();
    };
}

#endif // SERVER_SERVER_HPP
