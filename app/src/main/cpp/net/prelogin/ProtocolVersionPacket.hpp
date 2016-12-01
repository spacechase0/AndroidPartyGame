#ifndef NET_PRELOGIN_PROTOCOLVERSIONPACKET_HPP
#define NET_PRELOGIN_PROTOCOLVERSIONPACKET_HPP

#include "net/Packet.hpp"

namespace net
{
    namespace prelogin
    {
        /// This packet MUST maintain the same format across protocol versions.
        /// Client -> Server: Send the protocol version we are using to ensure compatibility
        /// Server -> Client: Send the appropriate version (so they know who is out of date),
        ///                   and then disconnect then.               
        class ProtocolVersionPacket : public Packet
        {
            public:
                ProtocolVersionPacket();
                
                virtual void read( Buffer& buffer ) override;
                virtual void write( Buffer& buffer ) const override;
                
                sf::Uint16 version = PROTOCOL_VERSION;
        };
    }
}

#endif // NET_PRELOGIN_PROTOCOLVERSIONPACKET_HPP

