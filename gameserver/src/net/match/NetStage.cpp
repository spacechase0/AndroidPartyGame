#include "net/match/NetStage.hpp"

#include "net/match/Packets.hpp"
#include "net/PacketId.hpp"

namespace net
{
    namespace match
    {
        std::unique_ptr< Packet > NetStage::getPacketFromId( Packet::Id id ) const
        {
            std::unique_ptr< Packet > ret;
            switch ( id )
            {
                //case PacketId::RequestMatchList: ret.reset( new RequestMatchListPacket() ); break;
            }
            return ret;
        }
    }
}
