#ifndef NET_MATCH_DICEROLLPACKET_HPP
#define NET_MATCH_DICEROLLPACKET_HPP

#include "net/Packet.hpp"

namespace net
{
    namespace match
    {
        class DiceRollPacket : public Packet
        {
            public:
                DiceRollPacket();
                DiceRollPacket( sf::Uint8 theNum );
                
                virtual void read( Buffer& buffer ) override;
                virtual void write( Buffer& buffer ) const override;
                
                //sf::Uint8 user;
                sf::Uint8 num;
        };
    }
}

#endif // NET_MATCH_DICEROLLPACKET_HPP
