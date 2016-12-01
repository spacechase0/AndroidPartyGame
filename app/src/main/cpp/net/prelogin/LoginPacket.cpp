#include "net/prelogin/LoginPacket.hpp"

#include "net/Buffer.hpp"
#include "net/PacketId.hpp"

namespace net
{
    namespace prelogin
    {
        LoginPacket::LoginPacket()
        :   LoginPacket( "", "" )
        {
        }
        
        LoginPacket::LoginPacket( const std::string& user, const std::string& pass )
        :   Packet( PacketId::Login ),
            username( user ),
            password( pass )
        {
        }
        
        void LoginPacket::read( Buffer& buffer )
        {
            buffer >> username >> password;
        }
        
        void LoginPacket::write( Buffer& buffer ) const
        {
            buffer << username << password;
        }
    }
}
