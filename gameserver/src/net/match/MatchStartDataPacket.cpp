#include "net/match/MatchStartDataPacket.hpp"

#include "net/Buffer.hpp"
#include "net/PacketId.hpp"

namespace net
{
    namespace match
    {
        MatchStartDataPacket::MatchStartDataPacket()
        :   Packet( PacketId::MatchStartData )
        {
        }
    
        void MatchStartDataPacket::read( Buffer& buffer )
        {
        }
        
        void MatchStartDataPacket::write( Buffer& buffer ) const
        {
        }
    }
}
