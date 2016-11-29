#ifndef NET_PRELOGIN_LOGINSTATUSPACKET_HPP
#define NET_PRELOGIN_LOGINSTATUSPACKET_HPP

#include "net/Packet.hpp"

namespace net
{
    namespace prelogin
    {
        class LoginStatusPacket : public Packet
        {
            public:
                LoginStatusPacket();
                
                virtual void read( Buffer& buffer ) override;
                virtual void write( Buffer& buffer ) const override;
                
                enum Status : sf::Uint8
                {
                    NoSuchUser,
                    LoginFailed,
                    LoginSuccessful,
                } status;
        };
    }
}

#endif // NET_PRELOGIN_LOGINSTATUSPACKET_HPP

