#include "server/match/NetStage.hpp"

#include "game/MatchData.hpp"
#include "net/match/Packets.hpp"
#include "net/PacketId.hpp"
#include "server/Client.hpp"
#include "server/ClientTransition.hpp"
#include "server/Match.hpp"
#include "server/Server.hpp"

namespace server
{
    namespace match
    {
        using namespace net;
        using namespace net::match;
        
        NetStage::NetStage( Server& theServer, Client& theClient, net::Connection& theConn, Match& theMatch )
        :   net::match::NetStage( theConn ),
            server( theServer ),
            client( theClient ),
            match( theMatch )
        {
            using namespace std::placeholders;
            
            //addHandler( PacketId::RequestMatchList, std::bind( &NetStage::handleRequestMatchList, this, _1 ) );
        }
        
        ClientTransition NetStage::getTransition() const
        {
            return ClientTransition( ClientTransition::Match );
        }
        
        Match& NetStage::getMatch()
        {
            return match;
        }
        
        const Match& NetStage::getMatch() const
        {
            return match;
        }
        
        /*void NetStage::handleRequestMatchList( const net::Packet* packet )
        {
            auto req = static_cast< const RequestMatchListPacket* >( packet );
            client.send( MatchListPacket( server.getMatchData() ) );
        }*/
    }
}
