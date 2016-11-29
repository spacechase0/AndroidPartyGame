#ifndef NET_PRELOGIN_LOGINPACKET_HPP
#define NET_PRELOGIN_LOGINPACKET_HPP

#include <string>

#include "net/Packet.hpp"

namespace net
{
    namespace prelogin
    {
        class LoginPacket : public Packet
        {
            public:
                LoginPacket();
                
                virtual void read( Buffer& buffer ) override;
                virtual void write( Buffer& buffer ) const override;
                
                std::string username;
                std::string password;
        };
    }
}

#endif // NET_PRELOGIN_LOGINPACKET_HPP

