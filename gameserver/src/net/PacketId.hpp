#ifndef NET_PACKETID_HPP
#define NET_PACKETID_HPP

#include "net/Packet.hpp"

namespace net
{
    enum PacketId : Packet::Id
    {
        ProtocolVersion,
        Register,
        Login,
        LoginStatus,
    };
}

#endif // NET_PACKETID_HPP
