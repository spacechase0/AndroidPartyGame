#ifndef NET_PACKETID_HPP
#define NET_PACKETID_HPP

#include "net/Packet.hpp"

namespace net
{
    enum PacketId : Packet::Id
    {
        // Prelobby
        ProtocolVersion,
        Register,
        Login,
        LoginStatus,
        
        // Lobby
        RequestMatchList,
        MatchList,
        CreateMatch,
        JoinMatch,
        MatchStatus,
    };
}

#endif // NET_PACKETID_HPP
