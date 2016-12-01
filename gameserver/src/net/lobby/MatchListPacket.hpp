#ifndef NET_LOBBY_MATCHLISTPACKET_HPP
#define NET_LOBBY_MATCHLISTPACKET_HPP

#include <vector>
#include <string>

#include "game/MatchData.hpp"
#include "net/Packet.hpp"

namespace net
{
    namespace lobby
    {
        class MatchListPacket : public Packet
        {
            public:
                MatchListPacket();
                MatchListPacket( const std::vector< game::MatchData >& theMatches );
                
                virtual void read( Buffer& buffer ) override;
                virtual void write( Buffer& buffer ) const override;
                
                std::vector< game::MatchData > matches;
        };
    }
}

#endif // NET_LOBBY_MATCHLISTPACKET_HPP
