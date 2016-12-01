#include "net/lobby/JoinMatchPacket.hpp"

#include "game/MatchData.hpp"
#include "net/Buffer.hpp"
#include "net/PacketId.hpp"

namespace net
{
    namespace lobby
    {
        JoinMatchPacket::JoinMatchPacket()
        :   JoinMatchPacket( game::MatchData() )
        {
        }
        
        JoinMatchPacket::JoinMatchPacket( const game::MatchData& match )
        :   Packet( PacketId::JoinMatch ),
            host( match.players.size() > 0 ? match.players[ 0 ] : "" )
        {
        }
    
        void JoinMatchPacket::read( Buffer& buffer )
        {
            buffer >> host;
        }
        
        void JoinMatchPacket::write( Buffer& buffer ) const
        {
            buffer << host;
        }
    }
}
