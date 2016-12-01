#ifndef CLIENT_LOBBY_NETSTAGE_HPP
#define CLIENT_LOBBY_NETSTAGE_HPP

#include <vector>

#include "game/MatchData.hpp"
#include "net/lobby/NetStage.hpp"
#include "net/lobby/MatchStatusCode.hpp"

namespace game
{
    class MatchData;
}

namespace client
{
    class Client;
    
    namespace lobby
    {
        class NetStage : public net::lobby::NetStage
        {
            public:
                NetStage( Client& theClient, net::Connection& theConn );
                
                net::lobby::MatchStatusCode lastStatus = net::lobby::MatchStatusCode::NONE;
                game::MatchData current;
                
                void getMatchList();
                void createMatch( const game::MatchData& match );
                void joinMatch( const game::MatchData& match );
                
                std::function< void ( const std::vector< game::MatchData >& ) > onMatchList;
                std::function< void ( const game::MatchData& data ) > onMatchStart;
            
            private:
                Client& client;
                
                void handleMatchList( const net::Packet* packet );
                void handleMatchStatus( const net::Packet* packet );
        };
    }
}

#endif // CLIENT_LOBBY_NETSTAGE_HPP
