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
    
    void Client::update()
    {
        if ( pendingStage )
        {
            stage = std::move( pendingStage );
            if ( onStageChange )
                onStageChange();
        }
        
        conn.update();
        if ( stage )
            stage->update();
    }
    
    bool Client::connect()
    {
        auto status = conn.socket.connect( sf::IpAddress( GAME_IP ), GAME_PORT );
        if ( status != sf::Socket::Done ) return false;
        conn.socket.setBlocking( false );
        
        stage.reset( new client::prelogin::NetStage( ( * this ), conn ) );
        send( new net::prelogin::ProtocolVersionPacket() );
        
        return true;
    }
    
    void Client::disconnect()
    {
        conn.socket.disconnect();
    }
    
    void Client::send( const net::Packet* packet )
    {
        stage->send( packet );
    }

    net::NetStage* Client::getNetStage()
    {
        return stage.get();
    }
    
    const net::NetStage* Client::getNetStage() const
    {
        return stage.get();
    }
    
    void Client::setNetStage( std::unique_ptr< net::NetStage > theStage )
    {
        pendingStage = std::move( theStage );
    }
}
