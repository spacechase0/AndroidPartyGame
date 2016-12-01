#ifndef NET_LOBBY_JOINMATCHPACKET_HPP
#define NET_LOBBY_JOINMATCHPACKET_HPP

#include <string>

#include "net/Packet.hpp"

namespace game
{
    class MatchData;
}

namespace net
{
    namespace lobby
    {
        class JoinMatchPacket : public Packet
        {
            public:
                JoinMatchPacket();
                JoinMatchPacket( const game::MatchData& match );
                
                virtual void read( Buffer& buffer ) override;
                virtual void write( Buffer& buffer ) const override;
                
                std::string host; /// TODO: Would be better as a global ID or something
        };
    }
}

#endif // NET_LOBBY_JOINMATCHPACKET_HPP
