#ifndef NET_MATCH_MATCHSTARTDATAPACKET_HPP
#define NET_MATCH_MATCHSTARTPDATAACKET_HPP

#include "game/MapData.hpp"
#include "game/PlayerData.hpp"
#include "net/Packet.hpp"

namespace net
{
    namespace match
    {
        class MatchStartDataPacket : public Packet
        {
            public:
                MatchStartDataPacket();
                MatchStartDataPacket( const game::MapData& theMap, const std::vector< game::PlayerData >& thePlayers );
                
                virtual void read( Buffer& buffer ) override;
                virtual void write( Buffer& buffer ) const override;
                
                game::MapData map;
                std::vector< game::PlayerData > players;
        };
    }
}

#endif // NET_MATCH_MATCHSTARTDATAPACKET_HPP
