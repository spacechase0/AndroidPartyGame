#include "server/lobby/NetStage.hpp"

#include "game/MatchData.hpp"
#include "net/lobby/Packets.hpp"
#include "net/PacketId.hpp"
#include "server/Client.hpp"
#include "server/ClientTransition.hpp"
#include "server/Match.hpp"
#include "server/Server.hpp"

namespace server
{
    namespace lobby
    {
        using namespace net;
        using namespace net::lobby;
        
        NetStage::NetStage( Server& theServer, Client& theClient, net::Connection& theConn )
        :   net::lobby::NetStage( theConn ),
            server( theServer ),
            client( theClient )
        {
            using namespace std::placeholders;
            
            addHandler( PacketId::RequestMatchList, std::bind( &handleRequestMatchList, this, _1 ) );
            addHandler( PacketId::CreateMatch,      std::bind( &handleCreateMatch,      this, _1 ) );
            addHandler( PacketId::JoinMatch,        std::bind( &handleJoinMatch,        this, _1 ) );
            addHandler( PacketId::MatchStatus,      std::bind( &handleMatchStatus,      this, _1 ) );
        }
        
        ClientTransition NetStage::getTransition() const
        {
            return ClientTransition( ClientTransition::Lobby );
        }
        
        void NetStage::handleRequestMatchList( const net::Packet* packet )
        {
            auto req = static_cast< const RequestMatchListPacket* >( packet );
            client.send( MatchListPacket( server.getMatchData() ) );
        }
        
        void NetStage::handleCreateMatch( const net::Packet* packet )
        {
            if ( current ) return;
            auto create = static_cast< const CreateMatchPacket* >( packet );
            
            std::unique_ptr< Match > match( new Match( server, create->match, &client ) );
            server.addMatch( std::move( match ) );
            client.send( MatchStatusPacket( JoinedMatch, match->asData() ) );
        }
        
        void NetStage::handleJoinMatch( const net::Packet* packet )
        {
            if ( current ) return;
            auto join = static_cast< const JoinMatchPacket* >( packet );
            
            MatchStatusPacket toSend;
            
            Match* match = server.findMatch( join->host );
            if ( match )
            {
                if ( match->getPlayers().size() == match->getMaxPlayers() )
                    toSend.status = MatchStatusCode::MatchWasFull;
                else
                {
                    toSend.status = MatchStatusCode::JoinedMatch;
                    toSend.match = match->asData();
                    current = match;
                }
            }
            else toSend.status = MatchStatusCode::MatchNotExist;
            
            send( toSend );
        }
        
        void NetStage::handleMatchStatus( const net::Packet* packet )
        {
            auto status = static_cast< const MatchStatusPacket* >( packet );
            if ( status->status == MatchStatusCode::LeftMatch )
            {
                if ( current )
                {
                    current->playerLeft( &client );
                    if ( current->getPlayers().size() == 0 )
                    {
                        server.removeMatch( current );
                    }
                    current = nullptr;
                }
            }
            else if ( status->status == MatchStatusCode::StartMatch )
            {
                if ( current && current->getHost() == &client )
                {
                    // TODO
                }
            }
        }
    }
}
