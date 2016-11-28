#include "client/Client.hpp"

#include <SFML/Network/IpAddress.hpp>

#include "client/prelogin/NetStage.hpp"
#include "net/prelogin/ProtocolVersionPacket.hpp"

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
        
        stage.reset( new client::prelogin::NetStage( * this ) );
        send( new net::prelogin::ProtocolVersionPacket() );
        
        return true;
    }
    
    void Client::disconnect()
    {
        conn.socket.disconnect();
    }
    
    void Client::send( const net::Packet* packet )
    {
        conn.write( packet );
    }
}
