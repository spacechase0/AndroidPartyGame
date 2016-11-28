#include "net/Connection.hpp"

#include "net/Packet.hpp"

namespace net
{
    void Connection::update()
    {
        char tmpBuffer[ RECV_BUFFER_SIZE ];
        
        std::size_t received = 0;
        if ( socket.receive( tmpBuffer, RECV_BUFFER_SIZE, received ) == sf::Socket::Done )
        {
            recvBuffer.write( tmpBuffer, received );
            recvBufferSize += received;
        }
        
        if ( sendBuffer.length() > 0 )
        {
            std::size_t sent = 0;
            auto status = socket.send( &sendBuffer[ 0 ], sendBuffer.length(), sent );
            if ( status == sf::Socket::Done && sent > 0 )
            {
                sendBuffer.erase( 0, sent );
            }
        }
    }
    
    std::size_t Connection::available() const
    {
        if ( recvBuffer.eof() ) return 0;
        
        // recvBuffer.tellg() is non-const. Sigh.
        auto curr = recvBuffer.rdbuf()->pubseekoff( 0, std::ios_base::cur, std::ios_base::in );
        
        return recvBufferSize - curr;
    }
    
    std::size_t Connection::read( void* data, std::size_t amount )
    {
        recvBuffer.readsome( static_cast< char* >( data ), amount );
        std::size_t amountRead = recvBuffer.gcount();
        
        // Reading doesn't 'consume' the string.
        // It only advances the spot we read from.
        // So, we need to clear the stuff we've already read every so often.
        if ( recvBuffer.tellg() >= RECV_BUFFER_REFRESH )
        {
            auto oldPos = recvBuffer.tellg();
            
            std::string newBuff = recvBuffer.str();
            newBuff.erase( 0, recvBuffer.tellg() );
            recvBufferSize = newBuff.length();
            
            recvBuffer.str( std::move( newBuff ) );
            
            recvBuffer.seekg( 0 );
        }
        
        return amountRead;
    }
    
    void Connection::write( void* data, std::size_t amount )
    {
        std::size_t sent = 0;
        socket.send( data, amount, sent );
        if ( sent < amount )
        {
            sendBuffer += std::string( static_cast< char* >( data ), amount );
        }
    }
    
    void Connection::write( const Packet* packet )
    {
        std::ostringstream oss;
        packet->write( oss );
        
        std::string data = oss.str();
        write( &data[ 0 ], data.length() );
    }
}
