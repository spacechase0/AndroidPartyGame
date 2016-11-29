#include "client/lobby/NetStage.hpp"

#include "client/Client.hpp"
#include "net/lobby/PacketId.hpp"
#include "net/lobby/Packets.hpp"

namespace client
{
    namespace lobby
    {
        using namespace net::lobby;
        
        NetStage::NetStage( Client& theClient, net::Connection& theConn )
        :   net::lobby::NetStage( theConn ),
            client( theClient )
        {
            using namespace std::placeholders;
        }
    }
}
