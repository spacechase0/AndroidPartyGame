#include "net/lobby/NetStage.hpp"

#include "net/lobby/Packets.hpp"
#include "net/PacketId.hpp"

namespace net
{
    namespace lobby
    {
        std::unique_ptr< Packet > NetStage::getPacketFromId( Packet::Id id ) const
        {
            std::unique_ptr< Packet > ret;
            switch ( id )
            {
            }
            return ret;
        }
    }
}
