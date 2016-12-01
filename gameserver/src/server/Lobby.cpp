#include "server/Lobby.hpp"

#include <SFML/System/Lock.hpp>

#include "server/Client.hpp"
#include "server/Server.hpp"

namespace server
{
    Lobby::Lobby( Server& theServer )
    :   server( theServer )
    {
    }
    
    Lobby::~Lobby()
    {
    }
    
    void Lobby::update()
    {
        {
            sf::Lock lock( clientsM );
            auto it = clients.begin();
            while ( it != clients.end() )
            {
                Client& client = ( * it->get() );
                client.update();
                
                if ( !client.isConnected() )
                {
                    it = clients.erase( it );
                }
                else ++it;
            }
        }
    }
    
    void Lobby::moveToLobby( std::unique_ptr< Client > client )
    {
        server.log( "[INFO] Client $ now in lobby.\n", client->user );
        sf::Lock lock( clientsM );
        clients.push_back( std::move( client ) );
        
    }
}
