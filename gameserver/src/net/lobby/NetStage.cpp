#include "net/lobby/NetStage.hpp"

#include "net/lobby/PacketId.hpp"
#include "net/lobby/Packets.hpp"

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
