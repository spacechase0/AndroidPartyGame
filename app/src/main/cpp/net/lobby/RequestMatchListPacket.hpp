#ifndef NET_LOBBY_REQUESTMATCHLISTPACKET_HPP
#define NET_LOBBY_REQUESTMATCHLISTPACKET_HPP

#include "net/Packet.hpp"

namespace net
{
    namespace lobby
    {
        class RequestMatchListPacket : public Packet
        {
            public:
                RequestMatchListPacket();
                
                virtual void read( Buffer& buffer ) override;
                virtual void write( Buffer& buffer ) const override;
        };
    }
}

#endif // NET_LOBBY_REQUESTMATCHLISTPACKET_HPP
