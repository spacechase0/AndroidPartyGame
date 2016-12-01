#include "net/match/MinigameStartPacket.hpp"

#include "net/Buffer.hpp"
#include "net/PacketId.hpp"

namespace net
{
    namespace match
    {
        MinigameStartPacket::MinigameStartPacket()
        :   Packet( PacketId::MinigameStart )
        {
        }
    
        void MinigameStartPacket::read( Buffer& buffer )
        {
            buffer >> minigameId;
        }
        
        void MinigameStartPacket::write( Buffer& buffer ) const
        {
            buffer << minigameId;
        }
    }
}
