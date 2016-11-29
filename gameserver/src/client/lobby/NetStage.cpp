#include "client/lobby/NetStage.hpp"

#include "client/Client.hpp"
#include "net/lobby/Packets.hpp"
#include "net/PacketId.hpp"

namespace client
{
    namespace lobby
    {
        using namespace net;
        using namespace net::lobby;
        
        NetStage::NetStage( Client& theClient, net::Connection& theConn )
        :   net::lobby::NetStage( theConn ),
            client( theClient )
        {
            using namespace std::placeholders;
            
            addHandler( PacketId::MatchList,   std::bind( &handleMatchList,   this, _1 ) );
            addHandler( PacketId::MatchStatus, std::bind( &handleMatchStatus, this, _1 ) );
        }
        
        void NetStage::getMatchList()
        {
            client.log( "[INFO] Requesting match list...\n" );
            client.send( RequestMatchListPacket() );
        }
        
        void NetStage::createMatch( const game::MatchData& match )
        {
            client.log( "[INFO] Creating a match called \"$\"...\n", match.name );
            client.send( CreateMatchPacket( match ) );
        }
        
        void NetStage::joinMatch( const game::MatchData& match )
        {
            client.log( "[INFO] Joining a match called \"$\"...\n", match.name );
            client.send( JoinMatchPacket( match ) );
        }
        
        void NetStage::handleMatchList( const net::Packet* packet )
        {
            auto matchList = static_cast< const MatchListPacket* >( packet );
            if ( onMatchList )
                onMatchList( matchList->matches );
        }
        
        void NetStage::handleMatchStatus( const net::Packet* packet )
        {
            auto status = static_cast< const MatchStatusPacket* >( packet );
            client.log("something match status\n");
        }
    }
}
