#ifndef CLIENT_PRELOGIN_NETSTAGE_HPP
#define CLIENT_PRELOGIN_NETSTAGE_HPP

#include "net/prelogin/LoginStatusCode.hpp"
#include "net/prelogin/NetStage.hpp"

namespace client
{
    class Client;
    
    namespace prelogin
    {
        class NetStage : public net::prelogin::NetStage
        {
            public:
                NetStage( Client& theClient, net::Connection& theConn );
                
                void login( const std::string& username, const std::string& password );
                void registerUser( const std::string& username, const std::string& password );
                
                net::prelogin::LoginStatusCode getLastLoginStatus();
            
            private:
                Client& client;
                net::prelogin::LoginStatusCode lastLoginStatus = net::prelogin::LoginStatusCode::NONE;
                
                void handleProtocolVersion( const net::Packet* packet );
                void handleLoginStatus( const net::Packet* packet );
        };
    }
}

#endif // CLIENT_PRELOGIN_NETSTAGE_HPP
