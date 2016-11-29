#include "net/NetStage.hpp"

#include <util/Endian.hpp>

#include "net/Buffer.hpp"
#include "net/Connection.hpp"

namespace net
{
    NetStage::NetStage( Connection& theConn )
    :   conn( theConn )
    {
    }
    
    NetStage::~NetStage()
    {
    }
    
    void NetStage::update()
    {
        if ( !pending )
        {
            if ( conn.available() < sizeof( pendingLen ) + sizeof( Packet::Id ) )
                return;
            
            pendingLen = conn.readValue< Packet::Length >();
            if ( util::LITTLE_ENDIAN )
                pendingLen = util::swapBytes( pendingLen );
            auto pendingId = conn.readValue< Packet::Id >();
            if ( util::LITTLE_ENDIAN )
                pendingId = util::swapBytes( pendingId );
            pending = getPacketFromId( pendingId );
        }
        if ( !pending ) return;
        
        if ( conn.available() < pendingLen )
            return;
        
        std::string str;
        str.resize( pendingLen );
        conn.read( &str[ 0 ], pendingLen );
        
        Buffer tmp( std::move( str ) );
        pending->read( tmp );
        
        auto handler = handlers.find( pending->id );
        if ( handler != handlers.end() )
        {
            handler->second( pending.get() );
        }
        pending.reset();
        pendingLen = -1;
    }
    
    void NetStage::addHandler( sf::Uint8 id, PacketHandler&& handler )
    {
        handlers[ id ] = handler;
    }
    
    void NetStage::send( const Packet* packet )
    {
        Buffer buffer;
        buffer << ( Packet::Length ) 0;
        buffer << ( util::LITTLE_ENDIAN ? util::swapBytes( packet->id ) : packet->id );
        packet->write( buffer );
        
        std::string data = buffer.data();
        Packet::Length len = static_cast< Packet::Length >( data.length() - 5 );
        ( * reinterpret_cast< Packet::Length* >( &data[ 0 ] ) ) = ( util::LITTLE_ENDIAN ? util::swapBytes( len ) : len );
        conn.write( &data[ 0 ], data.length() );
    }
}
