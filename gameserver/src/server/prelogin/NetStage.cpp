#include "server/prelogin/NetStage.hpp"

#include "server/Client.hpp"
#include "server/Server.hpp"
#include "net/prelogin/PacketId.hpp"
#include "net/prelogin/Packets.hpp"

namespace server
{
    namespace prelogin
    {
        using namespace net::prelogin;
        
        NetStage::NetStage( Server& theServer, Client& theClient, net::Connection& theConn )
        :   net::prelogin::NetStage( theConn ),
            server( theServer ),
            client( theClient )
        {
            using namespace std::placeholders;
            
            addHandler( PacketId::ProtocolVersion, std::bind( &handleProtocolVersion, this, _1 ) );
            addHandler( PacketId::Register,        std::bind( &handleRegister,        this, _1 ) );
            addHandler( PacketId::Login,           std::bind( &handleLogin,           this, _1 ) );
        }
        
        void NetStage::handleProtocolVersion( const net::Packet* packet )
        {
            auto ver = static_cast< const ProtocolVersionPacket* >( packet );
            if ( ver->version != PROTOCOL_VERSION )
            {
                server.log( "[INFO] Client protocol version didn't match. Client sent %i. (We're on %i.)\n", ver->version, PROTOCOL_VERSION );
                client.send( new ProtocolVersionPacket() );
                client.disconnect();
                return;
            }
            server.log( "[INFO] Client used correct protocol version.\n" );
        }
        
        void NetStage::handleRegister( const net::Packet* packet )
        {
            auto reg = static_cast< const RegisterPacket* >( packet );
            server.log( "[INFO] Client registered as %s.\n", reg->username );
            // TODO: Register
        }
        
        void NetStage::handleLogin( const net::Packet* packet )
        {
            auto login = static_cast< const LoginPacket* >( packet );
            server.log( "[INFO] Client attempting to login as %s.\n", login->username );
            // TODO: Login
            // TODO: Send login status
        }
    }
}
