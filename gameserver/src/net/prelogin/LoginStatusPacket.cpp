#include "net/prelogin/LoginStatusPacket.hpp"

#include "net/Buffer.hpp"
#include "net/PacketId.hpp"

namespace net
{
    namespace prelogin
    {
        LoginStatusPacket::LoginStatusPacket()
        :   LoginStatusPacket( LoginStatusCode::NONE )
        {
        }
        
        LoginStatusPacket::LoginStatusPacket( LoginStatusCode theStatus )
        :   Packet( PacketId::LoginStatus ),
            status( theStatus )
        {
        }
    
        void LoginStatusPacket::read( Buffer& buffer )
        {
            sf::Uint8 tmp;
            buffer >> tmp;
            status = static_cast< LoginStatusCode >( tmp );
        }
        
        void LoginStatusPacket::write( Buffer& buffer ) const
        {
            buffer << static_cast< sf::Uint8 >( status );
        }
    }
}
