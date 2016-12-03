#ifndef NET_MATCH_MINIGAMEENDPACKET_HPP
#define NET_MATCH_MINIGAMEENDPACKET_HPP

#include <vector>

#include "net/Packet.hpp"

namespace net
{
    namespace match
    {
        class MinigameEndPacket : public Packet
        {
            public:
                MinigameEndPacket();
                
                virtual void read( Buffer& buffer ) override;
                virtual void write( Buffer& buffer ) const override;
                
                std::vector< sf::Uint8 > winners;
        };
    }
}

#endif // NET_MATCH_MINIGAMEENDPACKET_HPP
