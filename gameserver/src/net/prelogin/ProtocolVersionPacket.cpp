#include "net/prelogin/ProtocolVersionPacket.hpp"

#include "net/Buffer.hpp"
#include "net/PacketId.hpp"

namespace net
{
    namespace prelogin
    {
        ProtocolVersionPacket::ProtocolVersionPacket()
        :   Packet( PacketId::ProtocolVersion )
        {
        }

        void ProtocolVersionPacket::read( Buffer& buffer )
        {
            buffer >> version;
        }
        
        void ProtocolVersionPacket::write( Buffer& buffer ) const
        {
            buffer << version;
        }
    }
}
