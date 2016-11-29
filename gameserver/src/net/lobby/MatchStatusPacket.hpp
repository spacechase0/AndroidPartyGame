#ifndef NET_LOBBY_MATCHSTATUSPACKET_HPP
#define NET_LOBBY_MATCHSTATUSPACKET_HPP

#include "game/MatchData.hpp"
#include "net/lobby/MatchStatusCode.hpp"
#include "net/Packet.hpp"

namespace net
{
    namespace lobby
    {
        class MatchStatusPacket : public Packet
        {
            public:
                MatchStatusPacket();
                MatchStatusPacket( MatchStatusCode theStatus, const game::MatchData& theMatch = game::MatchData() );
                
                virtual void read( Buffer& buffer ) override;
                virtual void write( Buffer& buffer ) const override;
                
                MatchStatusCode status;
                game::MatchData match;
        };
    }
}

#endif // NET_LOBBY_MATCHSTATUSPACKET_HPP
