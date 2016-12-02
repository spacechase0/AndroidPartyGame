#include "net/match/DiceRollPacket.hpp"

#include "net/Buffer.hpp"
#include "net/PacketId.hpp"

namespace net
{
    namespace match
    {
        DiceRollPacket::DiceRollPacket()
        :   DiceRollPacket( 0 )
        {
        }
        
        DiceRollPacket::DiceRollPacket( sf::Uint8 theNum )
        :   Packet( PacketId::DiceRoll ),
            num( theNum )
        {
        }
    
        void DiceRollPacket::read( Buffer& buffer )
        {
            buffer /*>> user*/ >> num;
        }
        
        void DiceRollPacket::write( Buffer& buffer ) const
        {
            buffer /*<< user*/ << num;
        }
    }
}
