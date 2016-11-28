#include "net/prelogin/LoginPacket.hpp"

#include "net/prelogin/PacketId.hpp"

namespace net
{
    namespace prelogin
    {
        LoginPacket::LoginPacket()
        :   Packet( PacketId::Login )
        {
        }
        
        unsigned int LoginPacket::getCurrentReadStage() const
        {
            return readStage;
        }
        
        unsigned int LoginPacket::getReadStageCount() const
        {
            return 2;
        }
        
        std::size_t LoginPacket::getCurrentReadStageSize() const
        {
            if ( readStage == 0 )
                return 4;
            else if ( readStage == 1 )
                return username.length() + password.length();
            
            return 0;
        }
        
        void LoginPacket::doReadStage( std::istream& in )
        {
            if ( readStage == 0 )
            {
                sf::Uint16 userLen, passLen;
                in >> userLen >> passLen;
                
                username.resize( userLen );
                password.resize( passLen );
            }
            else if ( readStage == 1 )
            {
                in.read( &username[ 0 ], username.length() );
                in.read( &password[ 0 ], password.length() );
            }
            ++readStage;
        }
        
        void LoginPacket::write( std::ostream& out ) const
        {
            sf::Uint16 userLen = static_cast< sf::Uint16 >( username.length() );
            sf::Uint16 passLen = static_cast< sf::Uint16 >( password.length() );
            
            out << userLen << passLen;
            
            out.write( &username[ 0 ], userLen );
            out.write( &password[ 0 ], passLen );
        }
    }
}
