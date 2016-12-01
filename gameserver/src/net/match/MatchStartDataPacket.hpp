#ifndef NET_MATCH_MATCHSTARTDATAPACKET_HPP
#define NET_MATCH_MATCHSTARTPDATAACKET_HPP

#include "net/Packet.hpp"

namespace net
{
    namespace match
    {
        class MatchStartDataPacket : public Packet
        {
            public:
                MatchStartDataPacket();
                
                virtual void read( Buffer& buffer ) override;
                virtual void write( Buffer& buffer ) const override;
        };
    }
}

#endif // NET_MATCH_MATCHSTARTDATAPACKET_HPP
