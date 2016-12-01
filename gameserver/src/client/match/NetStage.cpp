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
        
        NetStage::NetStage( Client& theClient, net::Connection& theConn )
        :   net::match::NetStage( theConn ),
            client( theClient )
        {
            using namespace std::placeholders;
            
            //addHandler( PacketId::MatchList,   std::bind( &NetStage::handleMatchList,   this, _1 ) );
        }
    }
}
