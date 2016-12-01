#include "net/match/DiceRollPacket.hpp"

#include "net/Buffer.hpp"
#include "net/PacketId.hpp"

namespace net
{
    namespace match
    {
        DiceRollPacket::DiceRollPacket()
        :   Packet( PacketId::DiceRoll )
        {
        }
    
        void DiceRollPacket::read( Buffer& buffer )
        {
            buffer >> user >> num;
        }
        
        void DiceRollPacket::write( Buffer& buffer ) const
        {
            buffer << user << num;
        }
    }
}
