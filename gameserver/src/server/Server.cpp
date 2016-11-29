#include "server/Server.hpp"

#include <memory>
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/System/Lock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Sleep.hpp>

#include "net/Connection.hpp"
#include "server/Client.hpp"
#include "server/DummyUserDatabase.hpp"
#include "server/Match.hpp"

namespace server
{
    Server::Server()
    :   log( "server.log" ),
        users( new DummyUserDatabase() ),
        listenerThread( &Server::listen, this )
    {
    }
    
    Server::~Server()
    {
    }
    
    void Server::run()
    {
        listenerThread.launch();
        
        while ( isRunning() )
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
            users->update();
            
            sf::sleep( sf::milliseconds( 10 ) );
        }
    }
    
    void Server::stop()
    {
        log( "[INFO] Stopping server...\n" );
        running = false;
        listener.close();
    }
    
    void Server::listen()
    {
        //sf::TcpListener listener;
        if ( listener.listen( GAME_PORT ) != sf::Socket::Done )
        {
            log( "[ERROR] Failed to listen. Stopping server.\n" );
            stop();
            return;
        }
        
        while ( isRunning() )
        {
            std::unique_ptr< net::Connection > conn( new net::Connection() );
            if ( listener.accept( conn->socket ) != sf::Socket::Done )
                continue;
            conn->socket.setBlocking( false );
            
            log( "[INFO] New connection.\n" );
            std::unique_ptr< Client > client( new Client( ( * this ), std::move( conn ) ) );
            
            sf::Lock lock( clientsM );
            clients.push_back( std::move( client ) );
        }
    }
}
