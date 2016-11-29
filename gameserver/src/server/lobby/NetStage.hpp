#ifndef SERVER_LOBBY_NETSTAGE_HPP
#define SERVER_LOBBY_NETSTAGE_HPP

#include "net/lobby/NetStage.hpp"
#include "server/ITransitioner.hpp"

namespace server
{
    class Client;
    class Server;
    
    namespace lobby
    {
        class NetStage : public net::lobby::NetStage, public ITransitioner
        {
            public:
                NetStage( Server& theServer, Client& theClient, net::Connection& theConn );
                
                virtual ClientTransition getTransition() const override;
            
            private:
                Server& server;
                Client& client;
        };
    }
}

#endif // SERVER_LOBBY_NETSTAGE_HPP
