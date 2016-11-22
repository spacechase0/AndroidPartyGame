#include "net/Connection.hpp"

namespace net
{
    void Connection::update()
    {
        char recvBuffer[ RECV_BUFFER_SIZE ];
        
        std::size_t received = 0;
        if ( socket.receive( recvBuffer, RECV_BUFFER_SIZE, received ) != sf::Socket::Done )
            return;
        
        buffer.write( recvBuffer, received );
        currBufferSize += received;
    }
    
    std::size_t Connection::available() const
    {
        if ( buffer.eof() ) return 0;
        
        // buffer.tellg() is non-const. Sigh.
        auto curr = buffer.rdbuf()->pubseekoff( 0, std::ios_base::cur, std::ios_base::in );
        
        return currBufferSize - curr;
    }
    
    std::size_t Connection::read( void* data, std::size_t amount )
    {
        buffer.readsome( static_cast< char* >( data ), amount );
        std::size_t amountRead = buffer.gcount();
        
        // Reading doesn't 'consume' the string.
        // It only advances the spot we read from.
        // So, we need to clear the stuff we've already read every so often.
        if ( buffer.tellg() >= RECV_BUFFER_REFRESH )
        {
            auto oldPos = buffer.tellg();
            
            std::string newBuff = buffer.str();
            newBuff.erase( 0, buffer.tellg() );
            currBufferSize = newBuff.length();
            
            buffer.str( std::move( newBuff ) );
            
            buffer.seekg( 0 );
        }
        
        return amountRead;
    }
}
