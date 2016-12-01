#include "net/match/MinigameInputDataPacket.hpp"

#include "net/Buffer.hpp"
#include "net/PacketId.hpp"

namespace net
{
    namespace match
    {
        MinigameInputDataPacket::MinigameInputDataPacket()
        :   Packet( PacketId::MinigameInputData )
        {
        }
    
        void MinigameInputDataPacket::read( Buffer& buffer )
        {
        }
        
        void MinigameInputDataPacket::write( Buffer& buffer ) const
        {
        }
    }
}
