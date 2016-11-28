#include "net/prelogin/NetStage.hpp"

#include "net/prelogin/PacketId.hpp"
#include "net/prelogin/Packets.hpp"

namespace net
{
    namespace prelogin
    {
        std::unique_ptr< Packet > NetStage::getPacketFromId( Packet::Id id ) const
        {
            std::unique_ptr< Packet > ret;
            switch ( id )
            {
                case PacketId::ProtocolVersion: ret.reset( new ProtocolVersionPacket() ); break;
                case PacketId::Register:        ret.reset( new RegisterPacket()        ); break;
                case PacketId::Login:           ret.reset( new LoginPacket()           ); break;
                case PacketId::LoginStatus:     ret.reset( new LoginStatusPacket()     ); break;
            }
            return ret;
        }
    }
}
