#ifndef NET_PRELOGIN_LOGINSTATUSPACKET_HPP
#define NET_PRELOGIN_LOGINSTATUSPACKET_HPP

#include "net/Packet.hpp"
#include "net/prelogin/LoginStatusCode.hpp"

namespace net
{
    namespace prelogin
    {
        class LoginStatusPacket : public Packet
        {
            public:
                LoginStatusPacket();
                LoginStatusPacket( LoginStatusCode theStatus );
                
                virtual void read( Buffer& buffer ) override;
                virtual void write( Buffer& buffer ) const override;
                
                LoginStatusCode status;
        };
    }
}

#endif // NET_PRELOGIN_LOGINSTATUSPACKET_HPP

