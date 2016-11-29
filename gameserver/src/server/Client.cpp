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
            
        if ( pendingStage )
        {
            stage = std::move( pendingStage );
            //if ( onStageChange )
            //    onStageChange();
        }
        
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
