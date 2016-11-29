#include "server/lobby/NetStage.hpp"

#include "server/Client.hpp"
#include "server/ClientTransition.hpp"
#include "server/Server.hpp"
#include "net/lobby/Packets.hpp"
#include "net/PacketId.hpp"

namespace server
{
    namespace lobby
    {
        using namespace net::lobby;
        
        NetStage::NetStage( Server& theServer, Client& theClient, net::Connection& theConn )
        :   net::lobby::NetStage( theConn ),
            server( theServer ),
            client( theClient )
        {
            using namespace std::placeholders;
        }
        
        ClientTransition NetStage::getTransition() const
        {
            return ClientTransition( ClientTransition::Lobby );
        }
    }
}
