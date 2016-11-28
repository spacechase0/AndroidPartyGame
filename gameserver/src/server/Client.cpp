#include "server/Client.hpp"

#include "net/Connection.hpp"
#include "net/NetStage.hpp"
#include "net/prelogin/NetStage.hpp"

namespace server
{
    Client::Client( Server& theServer )
    :   server( theServer )
    {
        stage.reset( new net::prelogin::NetStage() );
    }
    
    Client::~Client()
    {
    }
    
    void Client::update()
    {
        conn->update();
        stage->update( * conn );
    }
    
    void Client::send( const net::Packet* packet )
    {
        conn->write( packet );
    }
}
