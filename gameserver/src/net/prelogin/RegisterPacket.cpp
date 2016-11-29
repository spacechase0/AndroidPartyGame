#include "net/prelogin/RegisterPacket.hpp"

#include "net/Buffer.hpp"
#include "net/prelogin/PacketId.hpp"

namespace net
{
    namespace prelogin
    {
        RegisterPacket::RegisterPacket()
        :   Packet( PacketId::Register )
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
