#ifndef CLIENT_LOBBY_NETSTAGE_HPP
#define CLIENT_LOBBY_NETSTAGE_HPP

#include "net/lobby/NetStage.hpp"

namespace client
{
    class Client;
    
    namespace lobby
    {
        class NetStage : public net::lobby::NetStage
        {
            public:
                NetStage( Client& theClient, net::Connection& theConn );
            
            private:
                Client& client;
        };
    }
}

#endif // CLIENT_LOBBY_NETSTAGE_HPP
