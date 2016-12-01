#include "net/match/MinigameEndPacket.hpp"

#include "net/Buffer.hpp"
#include "net/PacketId.hpp"

namespace net
{
    namespace match
    {
        MinigameEndPacket::MinigameEndPacket()
        :   Packet( PacketId::MinigameEnd )
        {
        }
    
        void MinigameEndPacket::read( Buffer& buffer )
        {
            buffer >> winners;
        }
        
        void MinigameEndPacket::write( Buffer& buffer ) const
        {
            buffer << winners;
        }
    }
}
