#include "client/Client.hpp"

#include <SFML/Network/IpAddress.hpp>

namespace client
{
    Client::Client()
    :   log( "client" )
    {
    }
    
    bool Client::connect()
    {
        return socket.connect( sf::IpAddress( GAME_IP ), GAME_PORT ) == sf::Socket::Done;
    }
}
