#include "server/lobby/NetStage.hpp"

#include "server/Client.hpp"
#include "server/Server.hpp"
#include "net/lobby/PacketId.hpp"
#include "net/lobby/Packets.hpp"

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
    }
}
