#ifndef CLIENT_PRELOGIN_NETSTAGE_HPP
#define CLIENT_PRELOGIN_NETSTAGE_HPP

#include "net/prelogin/NetStage.hpp"

namespace client
{
    class Client;
    
    namespace prelogin
    {
        class NetStage : public net::prelogin::NetStage
        {
            public:
                NetStage( Client& theClient );
            
            private:
                Client& client;
                
                void handleProtocolVersion( const net::Packet* packet );
                void handleLoginStatus( const net::Packet* packet );
        };
    }
}

#endif // CLIENT_PRELOGIN_NETSTAGE_HPP
