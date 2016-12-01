#ifndef SERVER_LOBBY_NETSTAGE_HPP
#define SERVER_LOBBY_NETSTAGE_HPP

#include "net/lobby/NetStage.hpp"
#include "server/ITransitioner.hpp"

namespace server
{
    class Client;
    class Match;
    class Server;
    
    namespace lobby
    {
        class NetStage : public net::lobby::NetStage, public ITransitioner
        {
            public:
                NetStage( Server& theServer, Client& theClient, net::Connection& theConn );
                
                Match* current = nullptr;
                
                virtual ClientTransition getTransition() const override;
            
            private:
                Server& server;
                Client& client;
                
                void handleRequestMatchList( const net::Packet* packet );
                void handleCreateMatch( const net::Packet* packet );
                void handleJoinMatch( const net::Packet* packet );
                void handleMatchStatus( const net::Packet* packet );
        };
    }
}

#endif // SERVER_LOBBY_NETSTAGE_HPP
