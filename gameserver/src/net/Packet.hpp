#ifndef NET_PACKET_HPP
#define NET_PACKET_HPP

#include <cstddef>
#include <iostream>
#include <SFML/Config.hpp>

namespace net
{
    class Packet
    {
        public:
            typedef sf::Uint8 Id;
            typedef sf::Uint32 Length;
            
            Packet( Id theId );
            virtual ~Packet();
            
            const Id id;
            
            virtual unsigned int getCurrentReadStage() const = 0;
            virtual unsigned int getReadStageCount() const = 0;
            virtual std::size_t getCurrentReadStageSize() const = 0;
            virtual void doReadStage( std::istream& in ) = 0;
            
            virtual void write( std::ostream& out ) const = 0;
    };
}

#endif // NET_PACKET_HPP
