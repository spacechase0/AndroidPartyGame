#include "client/match/NetStage.hpp"

#include "client/Client.hpp"
#include "net/match/Packets.hpp"
#include "net/PacketId.hpp"

namespace client
{
    namespace match
    {
        using namespace net;
        using namespace net::match;
        
        NetStage::NetStage( Client& theClient, net::Connection& theConn, const game::MatchData& theMatch )
        :   net::match::NetStage( theConn ),
            client( theClient ),
            matchInfo( theMatch ),
            match( theClient, ( * this ) )
        {
            using namespace std::placeholders;
            
            addHandler( PacketId::MatchStartData, std::bind( &NetStage::handleMatchStartData, this, _1 ) );
        }
        
        void NetStage::handleMatchStartData( const net::Packet* packet )
        {
            auto data = static_cast< const MatchStartDataPacket* >( packet );
            
            client.log( "[INFO] Got match start data.\n" );
            map = data->map;
        }
    }
}
