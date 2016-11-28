#ifndef NET_PRELOGIN_PROTOCOLVERSIONPACKET_HPP
#define NET_PRELOGIN_PROTOCOLVERSIONPACKET_HPP

#include "net/SimplePacket.hpp"

namespace net
{
    namespace prelogin
    {
        /// This packet MUST maintain the same format across protocol versions.
        /// Client -> Server: Send the protocol version we are using to ensure compatibility
        /// Server -> Client: Send the appropriate version (so they know who is out of date),
        ///                   and then disconnect then.               
        class ProtocolVersionPacket : public net::SimplePacket
        {
            public:
                ProtocolVersionPacket();
                
                sf::Uint16 version = PROTOCOL_VERSION;
                
                virtual void write( std::ostream& out ) const override;
            
            protected:
                virtual std::size_t getSize() const override;
                virtual void read( std::istream& in ) override;
        };
    }
}

#endif // NET_PRELOGIN_PROTOCOLVERSIONPACKET_HPP

