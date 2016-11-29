#ifndef SERVER_LOBBY_NETSTAGE_HPP
#define SERVER_LOBBY_NETSTAGE_HPP

#include "net/lobby/NetStage.hpp"

namespace server
{
    class Client;
    class Server;
    
    namespace lobby
    {
        class NetStage : public net::lobby::NetStage
        {
            public:
                NetStage( Server& theServer, Client& theClient, net::Connection& theConn );
            
            private:
                Server& server;
                Client& client;
        };
    }
}

#endif // SERVER_LOBBY_NETSTAGE_HPP
