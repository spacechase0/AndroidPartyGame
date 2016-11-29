#include "net/lobby/CreateMatchPacket.hpp"

#include "net/Buffer.hpp"
#include "net/PacketId.hpp"

namespace net
{
    namespace lobby
    {
        CreateMatchPacket::CreateMatchPacket()
        :   CreateMatchPacket( game::MatchData() )
        {
        }
        
        CreateMatchPacket::CreateMatchPacket( const game::MatchData& theMatch )
        :   Packet( PacketId::RequestMatchList ),
            match( theMatch )
        {
        }
    
        void CreateMatchPacket::read( Buffer& buffer )
        {
            match = game::MatchData();
            buffer >> match.name >> match.maxPlayers;
        }
        
        void CreateMatchPacket::write( Buffer& buffer ) const
        {
            buffer << match.name << match.maxPlayers;
        }
    }
}
