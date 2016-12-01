#ifndef CLIENT_MATCH_NETSTAGE_HPP
#define CLIENT_MATCH_NETSTAGE_HPP

#include <vector>

#include "game/MapData.hpp"
#include "game/MatchData.hpp"
#include "net/match/NetStage.hpp"

namespace client
{
    class Client;
    
    namespace match
    {
        class NetStage : public net::match::NetStage
        {
            public:
                NetStage( Client& theClient, net::Connection& theConn, const game::MatchData& theMatch );
                
                game::MatchData match;
                game::MapData map;
            
            private:
                Client& client;
                
                void handleMatchStartData( const net::Packet* packet );
        };
    }
}

#endif // CLIENT_MATCH_NETSTAGE_HPP
