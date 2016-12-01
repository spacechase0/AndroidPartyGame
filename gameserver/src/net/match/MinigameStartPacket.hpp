#ifndef NET_MATCH_MINIGAMESTARTPACKET_HPP
#define NET_MATCH_MINIGAMESTARTPACKET_HPP

#include "net/Packet.hpp"

namespace net
{
    namespace match
    {
        class MinigameStartPacket : public Packet
        {
            public:
                MinigameStartPacket();
                
                virtual void read( Buffer& buffer ) override;
                virtual void write( Buffer& buffer ) const override;
                
                sf::Uint16 minigameId;
        };
    }
}

#endif // NET_MATCH_MINIGAMESTARTPACKET_HPP
