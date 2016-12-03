#include "client/prelogin/NetStage.hpp"

#include "client/Client.hpp"
#include "client/lobby/NetStage.hpp"
#include "net/PacketId.hpp"
#include "net/prelogin/Packets.hpp"

namespace client
{
    namespace prelogin
    {
        using namespace net;
        using namespace net::prelogin;
        
        NetStage::NetStage( Client& theClient, net::Connection& theConn )
        :   net::prelogin::NetStage( theConn ),
            client( theClient )
        {
            using namespace std::placeholders;
            
            addHandler( PacketId::ProtocolVersion, std::bind( &NetStage::handleProtocolVersion, this, _1 ) );
            addHandler( PacketId::LoginStatus,     std::bind( &NetStage::handleLoginStatus,     this, _1 ) );
        }
        
        void NetStage::login( const std::string& username, const std::string& password )
        {
            client.log( "[INFO] Logging in as $.\n", username );
            client.send( LoginPacket( username, password ) );
            client.user = username;
        }
        
        void NetStage::registerUser( const std::string& username, const std::string& password )
        {
            client.log( "[INFO] Registering as $.\n", username );
            client.send( RegisterPacket( username, password ) );
        }
        
        net::prelogin::LoginStatusCode NetStage::getLastLoginStatus()
        {
            auto status = lastLoginStatus;
            lastLoginStatus = net::prelogin::LoginStatusCode::NONE;
            return status;
        }
        
        void NetStage::handleProtocolVersion( const net::Packet* packet )
        {
            auto ver = static_cast< const ProtocolVersionPacket* >( packet );
            client.log( "[INFO] Protocol version didn't match. Server sent $. (We're on $.)\n", ver->version, PROTOCOL_VERSION );
            client.disconnect();
        }
        
        void NetStage::handleLoginStatus( const net::Packet* packet )
        {
            auto status = static_cast< const LoginStatusPacket* >( packet );
            //client.log( "[INFO] Login status: $\n", (int) status->status );
            lastLoginStatus = status->status;
            
            if ( lastLoginStatus == LoginStatusCode::LoginSuccessful )
            {
                client.setNetStage( std::unique_ptr< net::NetStage >( new client::lobby::NetStage( client, conn ) ) );
            }
            else client.user = "";
        }
    }
}
