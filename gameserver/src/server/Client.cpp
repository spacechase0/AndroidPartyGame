#include "server/Client.hpp"

#include "net/Connection.hpp"
#include "server/prelogin/NetStage.hpp"

namespace server
{
    Client::Client( Server& theServer, std::unique_ptr< net::Connection > theConn )
    :   server( theServer ),
        conn( std::move( theConn ) )
    {
        stage.reset( new server::prelogin::NetStage( server, ( * this ), ( * conn ) ) );
    }
    
    Client::~Client()
    {
    }
    
    void Client::update()
    {
        if ( !isConnected() )
            return;
        
        conn->update();
        stage->update();
    }
    
    void Client::disconnect()
    {
        conn->disconnect();
    }
    
    bool Client::isConnected() const
    {
        return conn->isConnected();
    }
    
    void Client::send( const net::Packet* packet )
    {
        stage->send( packet );
    }
}
