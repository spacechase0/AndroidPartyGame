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
                case PacketId::RequestMatchList: ret.reset( new RequestMatchListPacket() ); break;
                case PacketId::MatchList       : ret.reset( new MatchListPacket() ); break;
                case PacketId::CreateMatch     : ret.reset( new CreateMatchPacket() ); break;
                case PacketId::JoinMatch       : ret.reset( new JoinMatchPacket() ); break;
                case PacketId::MatchStatus     : ret.reset( new MatchStatusPacket() ); break;
            }
            return ret;
        }
    }
}
