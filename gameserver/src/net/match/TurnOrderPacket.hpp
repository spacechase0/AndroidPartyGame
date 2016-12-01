#ifndef NET_MATCH_TURNORDERPACKET_HPP
#define NET_MATCH_TURNORDERPACKET_HPP

#include <string>
#include <vector>

#include "net/Packet.hpp"

namespace net
{
    namespace match
    {
        class TurnOrderPacket : public Packet
        {
            public:
                TurnOrderPacket();
                
                virtual void read( Buffer& buffer ) override;
                virtual void write( Buffer& buffer ) const override;
                
                std::vector< std::string > order;
        };
    }
}

#endif // NET_MATCH_TURNORDERPACKET_HPP
