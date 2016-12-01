#ifndef NET_MATCH_MINIGAMEINPUTDATAPACKET_HPP
#define NET_MATCH_MINIGAMEINPUTDATAPACKET_HPP

#include "net/Packet.hpp"

namespace net
{
    namespace match
    {
        class MinigameInputDataPacket : public Packet
        {
            public:
                MinigameInputDataPacket();
                
                virtual void read( Buffer& buffer ) override;
                virtual void write( Buffer& buffer ) const override;
        };
    }
}

#endif // NET_MATCH_MINIGAMEINPUTDATAPACKET_HPP
