#include "net/lobby/MatchListPacket.hpp"

#include "net/Buffer.hpp"
#include "net/PacketId.hpp"

namespace
{
    net::Buffer& operator << ( net::Buffer& buffer, const game::MatchData& match )
    {
        buffer << match.name << match.maxPlayers << match.players;
        return buffer;
    }
    
    net::Buffer& operator >> ( net::Buffer& buffer, game::MatchData& match )
    {
        buffer >> match.name >> match.maxPlayers >> match.players;
        return buffer;
    }
}

namespace net
{
    namespace lobby
    {
        MatchListPacket::MatchListPacket()
        :   MatchListPacket( decltype( matches )() )
        {
        }
        
        MatchListPacket::MatchListPacket( const std::vector< game::MatchData >& theMatches )
        :   Packet( PacketId::MatchList ),
            matches( theMatches )
        {
        }
    
        void MatchListPacket::read( Buffer& buffer )
        {
            buffer >> matches;
        }
        
        void MatchListPacket::write( Buffer& buffer ) const
        {
            buffer << matches;
        }
    }
}
