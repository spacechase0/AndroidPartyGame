#include "net/match/TurnOrderPacket.hpp"

#include "net/Buffer.hpp"
#include "net/PacketId.hpp"

namespace net
{
    namespace match
    {
        TurnOrderPacket::TurnOrderPacket()
        :   Packet( PacketId::TurnOrder )
        {
        }
    
        void TurnOrderPacket::read( Buffer& buffer )
        {
            buffer >> order;
        }
        
        void TurnOrderPacket::write( Buffer& buffer ) const
        {
            buffer << order;
        }
    }
}
