#include "net/prelogin/RegisterPacket.hpp"

#include "net/Buffer.hpp"
#include "net/prelogin/PacketId.hpp"

namespace net
{
    namespace prelogin
    {
        RegisterPacket::RegisterPacket()
        :   RegisterPacket( "", "" )
        {
        }
        
        RegisterPacket::RegisterPacket( const std::string& user, const std::string& pass )
        :   Packet( PacketId::Register ),
            username( user ),
            password( pass )
        {
        }
        
        void RegisterPacket::read( Buffer& buffer )
        {
            buffer >> username >> password;
        }
        
        void RegisterPacket::write( Buffer& buffer ) const
        {
            buffer << username << password;
        }
    }
}
