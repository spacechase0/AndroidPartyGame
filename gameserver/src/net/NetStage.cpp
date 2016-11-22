#include "net/NetStage.hpp"

#include "net/Connection.hpp"

namespace net
{
    NetStage::~NetStage()
    {
    }
    
    void NetStage::update( Connection& conn )
    {
        if ( !pending )
        {
            if ( conn.available() < sizeof( pendingLen ) + sizeof( Packet::Id ) )
                return;
            
            pendingLen = conn.readValue< Packet::Length >();
            pending = getPacketFromId( conn.readValue< Packet::Id >() );
        }
        if ( !pending ) return;
        
        for ( unsigned int i = pending->getCurrentReadStage(); i < pending->getReadStageCount(); i = pending->getCurrentReadStage() )
        {
            std::size_t stageSize = pending->getCurrentReadStageSize();
            if ( conn.available() < stageSize )
                return;
            
            std::string buff( stageSize, ' ' );
            conn.read( &buff[ 0 ], stageSize );
            std::istringstream ss( buff );
            pending->doReadStage( ss );
        }
        
        auto handler = handlers.find( pending->id );
        if ( handler != handlers.end() )
        {
            handler->second( pending.get() );
        }
    }
    
    void NetStage::addHandler( sf::Uint8 id, PacketHandler&& handler )
    {
        handlers[ id ] = handler;
    }
}
