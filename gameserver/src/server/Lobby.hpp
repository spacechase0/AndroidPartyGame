#ifndef SERVER_LOBBY_HPP
#define SERVER_LOBBY_HPP

#include <list>
#include <memory>
#include <SFML/System/Mutex.hpp>

namespace server
{
    class Client;
    class Server;
    
    class Lobby
    {
        public:
            Lobby( Server& theServer );
            ~Lobby();
            
            void update();
            
            void moveToLobby( std::unique_ptr< Client > client );
        
        private:
            Server& server;
            
            sf::Mutex clientsM;
            std::list< std::unique_ptr< Client > > clients;
    };
}

#endif // SERVER_LOBBY_HPP
