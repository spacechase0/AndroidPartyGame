#ifndef NET_PACKET_HPP
#define NET_PACKET_HPP

#include <cstddef>
#include <SFML/Config.hpp>

namespace net
{
    class Buffer;
    
    class Packet
    {
        public:
            typedef sf::Uint8 Id;
            typedef sf::Uint32 Length;
            
            Packet( Id theId );
            virtual ~Packet();
            
            const Id id;
            
            virtual void read( Buffer& buffer ) = 0;
            virtual void write( Buffer& buffer ) const = 0;
    };
}

#endif // NET_PACKET_HPP
