#ifndef NET_PRELOGIN_NETSTAGE_HPP
#define NET_PRELOGIN_NETSTAGE_HPP

#include "net/NetStage.hpp"

namespace net
{
    namespace prelogin
    {
        class NetStage : public net::NetStage
        {
            protected:
                using net::NetStage::NetStage;
                
                virtual std::unique_ptr< Packet > getPacketFromId( Packet::Id id ) const;
        };
    }
}

#endif // NET_PRELOGIN_NETSTAGE_HPP
