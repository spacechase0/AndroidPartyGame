#include "server/Client.hpp"

#include "net/Connection.hpp"
#include "server/ITransitioner.hpp"
#include "server/lobby/NetStage.hpp"
#include "server/Match.hpp"
#include "server/match/NetStage.hpp"
#include "server/prelogin/NetStage.hpp"
#include "server/Server.hpp"

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
        auto lobbyStage = dynamic_cast< lobby::NetStage* >( stage.get() );
        if ( lobbyStage && lobbyStage->current )
        {
            lobbyStage->current->playerLeft( this );
            if ( lobbyStage->current->getPlayers().size() == 0 )
            {
                server.removeMatch( lobbyStage->current );
            }
            lobbyStage->current = nullptr;
            
            server.log( "[INFO] Client $ left the match.\n", user );
        }
        auto matchStage = dynamic_cast< match::NetStage* >( stage.get() );
        if ( matchStage )
        {
            matchStage->getMatch().playerLeft( this );
            if ( matchStage->getMatch().getPlayers().size() == 0 )
            {
                server.removeMatch( &matchStage->getMatch() );
            }
        }
        server.log( "[INFO] Client $ disconnected.\n", user );
    }
    
    ClientTransition Client::update()
    {
        if ( !isConnected() )
            return ClientTransition{ ClientTransition::None };;
            
        if ( pendingStage )
        {
            stage = std::move( pendingStage );
            auto transitioner = dynamic_cast< ITransitioner* >( stage.get() );
            if ( transitioner )
                return transitioner->getTransition();
            //if ( onStageChange )
            //    onStageChange();
        }
        
        conn->update();
        stage->update();
        
        return ClientTransition{ ClientTransition::None };
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
