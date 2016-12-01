#include "net/lobby/RequestMatchListPacket.hpp"

#include "net/Buffer.hpp"
#include "net/PacketId.hpp"

namespace net
{
    namespace lobby
    {
        RequestMatchListPacket::RequestMatchListPacket()
        :   Packet( PacketId::RequestMatchList )
        {
        }
    
        void RequestMatchListPacket::read( Buffer& buffer )
        {
        }
        
        void RequestMatchListPacket::write( Buffer& buffer ) const
        {
        }
    }
}
