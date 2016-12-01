#include "net/Buffer.hpp"

#include <stdexcept>
#include <util/Endian.hpp>

namespace 
{
    template< typename T >
    inline void read( std::istream& is, T& t )
    {
        is.read( reinterpret_cast< char* >( &t ), sizeof( T ) );
        if ( util::LITTLE_ENDIAN )
            t = util::swapBytes( t );
    }
    
    template< typename T >
    inline void write( std::ostream& os, T& t )
    {
        if ( util::LITTLE_ENDIAN )
            t = util::swapBytes( t );
        os.write( reinterpret_cast< char* >( &t ), sizeof( T ) );
    }
}

namespace net
{
    Buffer::Buffer()
    {
    }
    
    Buffer::Buffer( std::string data )
    :   ss( data )
    {
    }
    
    Buffer& Buffer::operator >> ( sf::Uint8& i )
    {
        read( ss, i );
        return ( * this );
    }
    
    Buffer& Buffer::operator >> ( sf::Uint16& i )
    {
        read( ss, i );
        return ( * this );
    }
    
    Buffer& Buffer::operator >> ( sf::Uint32& i )
    {
        read( ss, i );
        return ( * this );
    }
    
    Buffer& Buffer::operator >> ( sf::Int8& i )
    {
        read( ss, i );
        return ( * this );
    }
    
    Buffer& Buffer::operator >> ( sf::Int16& i )
    {
        read( ss, i );
        return ( * this );
    }
    
    Buffer& Buffer::operator >> ( sf::Int32& i )
    {
        read( ss, i );
        return ( * this );
    }
    
    Buffer& Buffer::operator >> ( std::string& str )
    {
        sf::Uint16 len;
        ( * this ) >> len;
        
        str.resize( len );
        ss.read( &str[ 0 ], len );
        
        return ( * this );
    }
    
    Buffer& Buffer::operator << ( sf::Uint8 i )
    {
        write( ss, i );
        return ( * this );
    }
    
    Buffer& Buffer::operator << ( sf::Uint16 i )
    {
        write( ss, i );
        return ( * this );
    }
    
    Buffer& Buffer::operator << ( sf::Uint32 i )
    {
        write( ss, i );
        return ( * this );
    }
    
    Buffer& Buffer::operator << ( sf::Int8 i )
    {
        write( ss, i );
        return ( * this );
    }
    
    Buffer& Buffer::operator << ( sf::Int16 i )
    {
        write( ss, i );
        return ( * this );
    }
    
    Buffer& Buffer::operator << ( sf::Int32 i )
    {
        write( ss, i );
        return ( * this );
    }
    
    Buffer& Buffer::operator << ( const std::string& str )
    {
        if ( str.size() > 65536 )
            throw std::invalid_argument( "String is too large for a packet." );
        
        sf::Uint16 len = static_cast< sf::Uint16 >( str.length() );
        ( * this ) << len;
        ss.write( &str[ 0 ], len );
        
        return ( * this );
    }
    
    std::string Buffer::data() const
    {
        return ss.str();
    }
}
