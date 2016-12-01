#ifndef NET_LOBBY_NETSTAGE_HPP
#define NET_LOBBY_NETSTAGE_HPP

#include "net/NetStage.hpp"

namespace net
{
    namespace lobby
    {
        class NetStage : public net::NetStage
        {
            protected:
                using net::NetStage::NetStage;
                
                virtual std::unique_ptr< Packet > getPacketFromId( Packet::Id id ) const;
        };
    }
}

#endif // NET_LOBBY_NETSTAGE_HPP
