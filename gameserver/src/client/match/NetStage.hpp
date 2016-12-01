#ifndef CLIENT_MATCH_NETSTAGE_HPP
#define CLIENT_MATCH_NETSTAGE_HPP

#include <vector>

#include "net/match/NetStage.hpp"

namespace game
{
    class MatchData;
}

namespace client
{
    class Client;
    
    namespace match
    {
        class NetStage : public net::match::NetStage
        {
            public:
                NetStage( Client& theClient, net::Connection& theConn );
            
            private:
                Client& client;
        };
    }
}

#endif // CLIENT_MATCH_NETSTAGE_HPP
