#include "net/prelogin/ProtocolVersionPacket.hpp"

#include "net/prelogin/PacketId.hpp"

namespace net
{
    namespace prelogin
    {
        ProtocolVersionPacket::ProtocolVersionPacket()
        :   SimplePacket( PacketId::ProtocolVersion )
        {
        }
        
        void ProtocolVersionPacket::write( std::ostream& out ) const
        {
            out << version;
        }
    
        std::size_t ProtocolVersionPacket::getSize() const
        {
            return sizeof( version );
        }

        void ProtocolVersionPacket::read( std::istream& in )
        {
            in >> version;
        }
    }
}
