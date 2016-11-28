#ifndef NET_PRELOGIN_PROTOCOLVERSIONPACKET_HPP
#define NET_PRELOGIN_PROTOCOLVERSIONPACKET_HPP

#include "net/SimplePacket.hpp"

namespace net
{
    namespace prelogin
    {
        class ProtocolVersionPacket : public net::SimplePacket
        {
            public:
                ProtocolVersionPacket();
                
                sf::Uint16 version = PROTOCOL_VERSION;
                
                virtual void write( std::ostream& out ) override;
            
            protected:
                virtual std::size_t getSize() const override;
                virtual void read( std::istream& in ) override;
        };
    }
}

#endif // NET_PRELOGIN_PROTOCOLVERSIONPACKET_HPP

