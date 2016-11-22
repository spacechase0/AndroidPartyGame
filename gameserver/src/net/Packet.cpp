#include "net/Packet.hpp"

namespace net
{
    Packet::Packet( Id theId )
    :   id( theId )
    {
    }
    
    Packet::~Packet()
    {
    }
}
