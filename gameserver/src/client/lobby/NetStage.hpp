#ifndef CLIENT_LOBBY_NETSTAGE_HPP
#define CLIENT_LOBBY_NETSTAGE_HPP

#include <vector>

#include "net/lobby/NetStage.hpp"

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
                
                void getMatchList();
                void createMatch( const game::MatchData& match );
                void joinMatch( const game::MatchData& match );
                
                std::function< void ( const std::vector< game::MatchData >& ) > onMatchList;
            
            private:
                Client& client;
                
                void handleMatchList( const net::Packet* packet );
                void handleMatchStatus( const net::Packet* packet );
        };
    }
}

#endif // CLIENT_LOBBY_NETSTAGE_HPP
