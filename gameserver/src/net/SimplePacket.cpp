#include "net/SimplePacket.hpp"

namespace net
{
    unsigned int SimplePacket::getCurrentReadStage() const
    {
        return haveRead ? 1 : 0;
    }
    
    unsigned int SimplePacket::getReadStageCount() const
    {
        return 1;
    }
    
    std::size_t SimplePacket::getCurrentReadStageSize() const
    {
        return getSize();
    }
    
    void SimplePacket::doReadStage( std::istream& in )
    {
        read( in );
        haveRead = true;
    }
}
