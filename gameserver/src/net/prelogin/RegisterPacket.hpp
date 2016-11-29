#ifndef NET_PRELOGIN_REGISTERPACKET_HPP
#define NET_PRELOGIN_REGISTERPACKET_HPP

#include <string>

#include "net/Packet.hpp"

namespace net
{
    namespace prelogin
    {
        class RegisterPacket : public Packet
        {
            public:
                RegisterPacket();
                
                virtual void read( Buffer& buffer ) override;
                virtual void write( Buffer& buffer ) const override;
                
                std::string username;
                std::string password;
        };
    }
}

#endif // NET_PRELOGIN_REGISTERPACKET_HPP

