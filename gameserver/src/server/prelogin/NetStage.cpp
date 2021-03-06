#include "server/prelogin/NetStage.hpp"

#include "server/Client.hpp"
#include "server/IUserDatabase.hpp"
#include "server/lobby/NetStage.hpp"
#include "server/Server.hpp"
#include "net/PacketId.hpp"
#include "net/prelogin/Packets.hpp"

namespace server
{
    namespace prelogin
    {
        using namespace net;
        using namespace net::prelogin;
        
        NetStage::NetStage( Server& theServer, Client& theClient, net::Connection& theConn )
        :   net::prelogin::NetStage( theConn ),
            server( theServer ),
            client( theClient )
        {
            using namespace std::placeholders;
            
            addHandler( PacketId::ProtocolVersion, std::bind( &NetStage::handleProtocolVersion, this, _1 ) );
            addHandler( PacketId::Register,        std::bind( &NetStage::handleRegister,        this, _1 ) );
            addHandler( PacketId::Login,           std::bind( &NetStage::handleLogin,           this, _1 ) );
        }
        
        void NetStage::handleProtocolVersion( const net::Packet* packet )
        {
            auto ver = static_cast< const ProtocolVersionPacket* >( packet );
            if ( ver->version != PROTOCOL_VERSION )
            {
                server.log( "[INFO] Client protocol version didn't match. Client sent $. (We're on $.)\n", ver->version, PROTOCOL_VERSION );
                client.send( ProtocolVersionPacket() );
                client.disconnect();
                return;
            }
            server.log( "[INFO] Client used correct protocol version.\n" );
        }
        
        void NetStage::handleRegister( const net::Packet* packet )
        {
            auto reg = static_cast< const RegisterPacket* >( packet );
            
            std::string username = reg->username;
            server.users->registerUser( reg->username, reg->password,
            [ this, username ]( net::prelogin::LoginStatusCode status )
            {
                if ( status == net::prelogin::LoginStatusCode::RegisterSuccessful )
                    server.log( "[INFO] Client registered as $.\n", username );
                client.send( LoginStatusPacket( status ) );
            } );
        }
        
        void NetStage::handleLogin( const net::Packet* packet )
        {
            auto login = static_cast< const LoginPacket* >( packet );
            
            std::string username = login->username;
            server.users->checkLogin( login->username, login->password,
            [ this, username ]( net::prelogin::LoginStatusCode status )
            {
                if ( status == net::prelogin::LoginStatusCode::LoginSuccessful )
                {
                    server.log( "[INFO] Client logged in as $.\n", username );
                    client.setNetStage( std::unique_ptr< net::NetStage >( new server::lobby::NetStage( server, client, conn ) ) );
                    client.user = username;
                }
                client.send( LoginStatusPacket( status ) );
            } );
        }
    }
}
