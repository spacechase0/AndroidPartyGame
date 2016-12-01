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
                case PacketId::MatchStartData:    ret.reset( new MatchStartDataPacket() ); break;
                case PacketId::DiceRoll:          ret.reset( new DiceRollPacket() ); break;
                case PacketId::TurnOrder:         ret.reset( new TurnOrderPacket() ); break;
                case PacketId::MinigameStart:     ret.reset( new MinigameStartPacket() ); break;
                case PacketId::MinigameInputData: ret.reset( new MinigameInputDataPacket() ); break;
                case PacketId::MinigameStateData: ret.reset( new MinigameStateDataPacket() ); break;
                case PacketId::MinigameEnd:       ret.reset( new MinigameEndPacket() ); break;
            }
            return ret;
        }
    }
}
