#ifndef NET_LOBBY_CREATEMATCHPACKET_HPP
#define NET_LOBBY_CREATEMATCHPACKET_HPP

#include "game/MatchData.hpp"
#include "net/Packet.hpp"

namespace net
{
    namespace lobby
    {
        class CreateMatchPacket : public Packet
        {
            public:
                CreateMatchPacket();
                CreateMatchPacket( const game::MatchData& theMatch );
                
                virtual void read( Buffer& buffer ) override;
                virtual void write( Buffer& buffer ) const override;
                
                game::MatchData match;
        };
    }
}

#endif // NET_LOBBY_CREATEMATCHPACKET_HPP
