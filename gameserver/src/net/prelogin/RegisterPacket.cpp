#include "net/prelogin/RegisterPacket.hpp"

#include "net/prelogin/PacketId.hpp"

namespace net
{
    namespace prelogin
    {
        RegisterPacket::RegisterPacket()
        :   Packet( PacketId::Register )
        {
        }
        
        unsigned int RegisterPacket::getCurrentReadStage() const
        {
            return readStage;
        }
        
        unsigned int RegisterPacket::getReadStageCount() const
        {
            return 2;
        }
        
        std::size_t RegisterPacket::getCurrentReadStageSize() const
        {
            if ( readStage == 0 )
                return 4;
            else if ( readStage == 1 )
                return username.length() + password.length();
            
            return 0;
        }
        
        void RegisterPacket::doReadStage( std::istream& in )
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
        
        void RegisterPacket::write( std::ostream& out )
        {
            sf::Uint16 userLen = static_cast< sf::Uint16 >( username.length() );
            sf::Uint16 passLen = static_cast< sf::Uint16 >( password.length() );
            
            out << userLen << passLen;
            
            out.write( &username[ 0 ], userLen );
            out.write( &password[ 0 ], passLen );
        }
    }
}
