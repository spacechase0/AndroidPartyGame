#include "net/match/MinigameStateDataPacket.hpp"

#include "net/Buffer.hpp"
#include "net/PacketId.hpp"

namespace net
{
    namespace match
    {
        MinigameStateDataPacket::MinigameStateDataPacket()
        :   Packet( PacketId::MinigameStateData )
        {
        }
    
        void MinigameStateDataPacket::read( Buffer& buffer )
        {
        }
        
        void MinigameStateDataPacket::write( Buffer& buffer ) const
        {
        }
    }
}
