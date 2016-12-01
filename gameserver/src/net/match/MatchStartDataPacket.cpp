#include "net/match/MatchStartDataPacket.hpp"

#include "net/Buffer.hpp"
#include "net/PacketId.hpp"

namespace net
{
    namespace match
    {
        MatchStartDataPacket::MatchStartDataPacket()
        :   MatchStartDataPacket( game::MapData() )
        {
        }
    
        MatchStartDataPacket::MatchStartDataPacket( const game::MapData& theMap )
        :   Packet( PacketId::MatchStartData ),
            map( theMap )
        {
        }
    
        void MatchStartDataPacket::read( Buffer& buffer )
        {
            buffer >> map;
        }
        
        void MatchStartDataPacket::write( Buffer& buffer ) const
        {
            buffer << map;
        }
    }
}
