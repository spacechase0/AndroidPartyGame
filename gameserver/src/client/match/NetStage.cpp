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
            match( theMatch )
        {
            using namespace std::placeholders;
            
            //addHandler( PacketId::MatchList,   std::bind( &NetStage::handleMatchList,   this, _1 ) );
        }
    }
}
