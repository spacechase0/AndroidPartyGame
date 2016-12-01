#ifndef NET_MATCH_NETSTAGE_HPP
#define NET_MATCH_NETSTAGE_HPP

#include "net/NetStage.hpp"

namespace net
{
    namespace match
    {
        class NetStage : public net::NetStage
        {
            protected:
                using net::NetStage::NetStage;
                
                virtual std::unique_ptr< Packet > getPacketFromId( Packet::Id id ) const;
        };
    }
}

#endif // NET_MATCH_NETSTAGE_HPP
