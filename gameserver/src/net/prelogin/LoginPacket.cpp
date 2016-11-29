#include "net/prelogin/LoginPacket.hpp"

#include "net/Buffer.hpp"
#include "net/prelogin/PacketId.hpp"

namespace net
{
    namespace prelogin
    {
        LoginPacket::LoginPacket()
        :   Packet( PacketId::Login )
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
