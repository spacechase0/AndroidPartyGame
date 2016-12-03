#include "net/match/MatchStartDataPacket.hpp"

#include "net/Buffer.hpp"
#include "net/PacketId.hpp"

namespace net
{
    namespace match
    {
        MatchStartDataPacket::MatchStartDataPacket()
        :   MatchStartDataPacket( game::MapData(), std::vector< game::PlayerData >() )
        {
        }
    
        MatchStartDataPacket::MatchStartDataPacket( const game::MapData& theMap, const std::vector< game::PlayerData >& thePlayers )
        :   Packet( PacketId::MatchStartData ),
            map( theMap ),
            players( thePlayers )
        {
        }
    
        void MatchStartDataPacket::read( Buffer& buffer )
        {
            buffer >> map >> players;
        }
        
        void MatchStartDataPacket::write( Buffer& buffer ) const
        {
            buffer << map << players;
        }
    }
}
