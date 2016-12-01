#include "net/lobby/MatchStatusPacket.hpp"

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
        MatchStatusPacket::MatchStatusPacket()
        :   MatchStatusPacket( MatchStatusCode::NONE )
        {
        }
        
        MatchStatusPacket::MatchStatusPacket( MatchStatusCode theStatus, const game::MatchData& theMatch )
        :   Packet( PacketId::MatchStatus ),
            status( theStatus ),
            match( theMatch )
        {
        }
    
        void MatchStatusPacket::read( Buffer& buffer )
        {
            sf::Uint8 tmp;
            buffer >> tmp;
            status = static_cast< MatchStatusCode >( tmp );
            
            if ( status == MatchStatusCode::JoinedMatch || status == MatchStatusCode::MatchStatus || status == MatchStatusCode::StartMatch )
            {
                buffer >> match;
            }
        }
        
        void MatchStatusPacket::write( Buffer& buffer ) const
        {
            buffer << static_cast< sf::Uint8 >( status );
            if ( status == MatchStatusCode::JoinedMatch || status == MatchStatusCode::MatchStatus || status == MatchStatusCode::StartMatch )
            {
                buffer << match;
            }
        }
    }
}
