#ifndef NET_PRELOGIN_REGISTERPACKET_HPP
#define NET_PRELOGIN_REGISTERPACKET_HPP

#include "net/Packet.hpp"

namespace net
{
    namespace prelogin
    {
        class RegisterPacket : public Packet
        {
            public:
                RegisterPacket();
                
                virtual unsigned int getCurrentReadStage() const override;
                virtual unsigned int getReadStageCount() const override;
                virtual std::size_t getCurrentReadStageSize() const override;
                virtual void doReadStage( std::istream& in ) override;
                
                virtual void write( std::ostream& out ) const override;
                
                std::string username;
                std::string password;
            
            private:
                unsigned int readStage = 0;
        };
    }
}

#endif // NET_PRELOGIN_REGISTERPACKET_HPP

