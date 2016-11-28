#include "net/prelogin/LoginStatusPacket.hpp"

#include "net/prelogin/PacketId.hpp"

namespace net
{
    namespace prelogin
    {
        LoginStatusPacket::LoginStatusPacket()
        :   SimplePacket( PacketId::LoginStatus )
        {
        }
        
        void LoginStatusPacket::write( std::ostream& out )
        {
            out << status;
        }
    
        std::size_t LoginStatusPacket::getSize() const
        {
            return sizeof( status );
        }

        void LoginStatusPacket::read( std::istream& in )
        {
            sf::Uint8 tmp;
            in >> tmp;
            status = static_cast< Status >( tmp );
        }
    }
}
