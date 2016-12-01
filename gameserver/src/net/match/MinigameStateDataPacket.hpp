#ifndef NET_MATCH_MINIGAMESTATEDATAPACKET_HPP
#define NET_MATCH_MINIGAMESTATEDATAPACKET_HPP

#include "net/Packet.hpp"

namespace net
{
    namespace match
    {
        class MinigameStateDataPacket : public Packet
        {
            public:
                MinigameStateDataPacket();
                
                virtual void read( Buffer& buffer ) override;
                virtual void write( Buffer& buffer ) const override;
        };
    }
}

#endif // NET_MATCH_MINIGAMESTATEDATAPACKET_HPP
