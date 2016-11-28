#ifndef NET_PRELOGIN_PACKETID_HPP
#define NET_PRELOGIN_PACKETID_HPP

#include "net/Packet.hpp"

namespace net
{
    namespace prelogin
    {
        enum PacketId : Packet::Id
        {
            ProtocolVersion,
            Register,
            Login,
            LoginStatus,
        };
    }
}

#endif // NET_PRELOGIN_PACKETID_HPP
