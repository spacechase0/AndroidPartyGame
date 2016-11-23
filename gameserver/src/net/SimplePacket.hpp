#ifndef NET_SIMPLEPACKET_HPP
#define NET_SIMPLEPACKET_HPP

#include "net/Packet.hpp"

namespace net
{
    /// Children will only have to implement:
    ///     virtual std::size_t getSize() const
    ///     virtual void read( std::istream& in )
    ///     virtual void write( std::ostream& out )
    /// Sadly things using strings (that aren't a fixed length)
    /// Will have to do things staged.
    class SimplePacket : public Packet
    {
        public:
            using Packet::Packet;
            
            virtual unsigned int getCurrentReadStage() const ;
            virtual unsigned int getReadStageCount() const;
            virtual std::size_t getCurrentReadStageSize() const;
            virtual void doReadStage( std::istream& in );
            
        protected:
            virtual std::size_t getSize() const = 0;
            virtual void read( std::istream& in ) = 0;
        
        private:
            bool haveRead = false;
    };
}

#endif // NET_SIMPLEPACKET_HPP
