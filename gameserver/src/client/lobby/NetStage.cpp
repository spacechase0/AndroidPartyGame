#include "client/lobby/NetStage.hpp"

#include "client/Client.hpp"
#include "client/match/NetStage.hpp"
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
            
            addHandler( PacketId::MatchList,   std::bind( &NetStage::handleMatchList,   this, _1 ) );
            addHandler( PacketId::MatchStatus, std::bind( &NetStage::handleMatchStatus, this, _1 ) );
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
            lastStatus = status->status;
            switch ( status->status )
            {
                case net::lobby::MatchStatusCode::MatchNotExist: client.log( "[INFO] The match we wanted to join doesn't exist.\n" ); break;
                case net::lobby::MatchStatusCode::MatchWasFull: client.log( "[INFO] The match we wanted to join is full.\n" ); break;
                case net::lobby::MatchStatusCode::KickedFromMatch:
                    client.log( "[INFO] We were kicked from the match.\n" );
                    current = game::MatchData();
                    break;
                case net::lobby::MatchStatusCode::JoinedMatch:
                    client.log( "[INFO] We joined the match.\n" );
                    current = status->match;
                    break;break;
                case net::lobby::MatchStatusCode::StartMatch:
                    {
                        client.log( "[INFO] The match started!\n" );
                        client.setNetStage( std::unique_ptr< net::NetStage >( new client::match::NetStage( client, conn, current ) ) );
                        if ( onMatchStart )
                            onMatchStart( current );
                        break;
                    }
                default: break;
            }
        }
    }
}
