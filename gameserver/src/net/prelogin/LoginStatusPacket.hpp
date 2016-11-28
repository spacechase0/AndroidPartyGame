#ifndef NET_PRELOGIN_LOGINSTATUSPACKET_HPP
#define NET_PRELOGIN_LOGINSTATUSPACKET_HPP

#include "net/SimplePacket.hpp"

namespace net
{
    namespace prelogin
    {
        class LoginStatusPacket : public net::SimplePacket
        {
            public:
                LoginStatusPacket();
                
                enum Status : sf::Uint8
                {
                    NoSuchUser,
                    LoginFailed,
                    LoginSuccessful,
                } status;
                
                virtual void write( std::ostream& out ) override;
            
            protected:
                virtual std::size_t getSize() const override;
                virtual void read( std::istream& in ) override;
        };
    }
}

#endif // NET_PRELOGIN_LOGINSTATUSPACKET_HPP

