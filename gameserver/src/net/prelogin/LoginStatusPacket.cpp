#include "net/prelogin/LoginStatusPacket.hpp"

#include "net/Buffer.hpp"
#include "net/prelogin/PacketId.hpp"

namespace net
{
    namespace prelogin
    {
        LoginStatusPacket::LoginStatusPacket()
        :   Packet( PacketId::LoginStatus )
        {
        }
    
        void LoginStatusPacket::read( Buffer& buffer )
        {
            sf::Uint8 tmp;
            buffer >> tmp;
            status = static_cast< Status >( tmp );
        }
        
        void LoginStatusPacket::write( Buffer& buffer ) const
        {
            buffer << status;
        }
    }
}
