#include "client/prelogin/NetStage.hpp"

#include "client/Client.hpp"
#include "net/prelogin/PacketId.hpp"
#include "net/prelogin/Packets.hpp"

namespace client
{
    namespace prelogin
    {
        using namespace net::prelogin;
        
        NetStage::NetStage( Client& theClient )
        :   client( theClient )
        {
            using namespace std::placeholders;
            
            addHandler( PacketId::ProtocolVersion, std::bind( &handleProtocolVersion, this, _1 ) );
            addHandler( PacketId::LoginStatus,     std::bind( &handleLoginStatus,     this, _1 ) );
        }
        
        void NetStage::handleProtocolVersion( const net::Packet* packet )
        {
            auto ver = static_cast< const ProtocolVersionPacket* >( packet );
            client.log( "[INFO] Protocol version didn't match. Server sent %i. (We're on %i.)\n", ver->version, PROTOCOL_VERSION );
            client.disconnect();
        }
        
        void NetStage::handleLoginStatus( const net::Packet* packet )
        {
            auto status = static_cast< const LoginStatusPacket* >( packet );
            client.log( "[INFO] Login status: %i\n", (int) status->status );
        }
    }
}
