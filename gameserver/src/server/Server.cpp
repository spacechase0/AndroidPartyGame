#include "server/Server.hpp"

#include <iostream> // TODO: Remove ref and give proper logging solution
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Sleep.hpp>

#include "server/Client.hpp"
#include "server/Match.hpp"

namespace server
{
    Server::Server()
    :   log( "server" ),
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
            for ( Client& client : clients )
            {
            }
            
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
            sf::TcpSocket socket;
            if ( listener.accept( socket ) != sf::Socket::Done )
                continue;
            
            log( "[INFO] New connection.\n" );
            // TODO: Add client
        }
    }
}
