#ifndef SERVER_MATCH_NETSTAGE_HPP
#define SERVER_MATCH_NETSTAGE_HPP

#include "net/match/NetStage.hpp"
#include "server/ITransitioner.hpp"

namespace server
{
    class Client;
    class Match;
    class Server;
    
    namespace match
    {
        class NetStage : public net::match::NetStage, public ITransitioner
        {
            public:
                NetStage( Server& theServer, Client& theClient, net::Connection& theConn, Match& theMatch );
                
                virtual ClientTransition getTransition() const override;
                
                Match& getMatch();
                const Match& getMatch() const;
            
            private:
                Server& server;
                Client& client;
                Match& match;
                
                //void handleRequestMatchList( const net::Packet* packet );
        };
    }
}

#endif // SERVER_MATCH_NETSTAGE_HPP
