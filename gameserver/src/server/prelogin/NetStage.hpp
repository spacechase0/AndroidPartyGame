#ifndef SERVER_PRELOGIN_NETSTAGE_HPP
#define SERVER_PRELOGIN_NETSTAGE_HPP

#include "net/prelogin/NetStage.hpp"

namespace server
{
    class Client;
    class Server;
    
    namespace prelogin
    {
        class NetStage : public net::prelogin::NetStage
        {
            public:
                NetStage( Server& theServer, Client& theClient, net::Connection& theConn );
            
            private:
                Server& server;
                Client& client;
                
                void handleProtocolVersion( const net::Packet* packet );
                void handleRegister( const net::Packet* packet );
                void handleLogin( const net::Packet* packet );
        };
    }
}

#endif // SERVER_PRELOGIN_NETSTAGE_HPP
