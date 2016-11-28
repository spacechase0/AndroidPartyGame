#include "client/Client.hpp"

#include <SFML/Network/IpAddress.hpp>

namespace client
{
    Client::Client()
    :   log( "client.log" )
    {
    }
    
    bool Client::connect()
    {
        auto status = conn.socket.connect( sf::IpAddress( GAME_IP ), GAME_PORT );
        if ( status != sf::Socket::Done ) return false;
        
        // set netstage
        // send protocol version
        
        return true;
    }
}
