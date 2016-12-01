#ifndef NET_BUFFER_HPP
#define NET_BUFFER_HPP

#include <map>
#include <SFML/System/Vector2.hpp>
#include <string>
#include <sstream>
#include <vector>

namespace net
{
    class Buffer
    {
        public:
            Buffer();
            Buffer( std::string data );
            
            Buffer& operator >> ( bool& b );
            Buffer& operator >> ( sf::Uint8& i );
            Buffer& operator >> ( sf::Uint16& i );
            Buffer& operator >> ( sf::Uint32& i );
            Buffer& operator >> ( sf::Int8& i );
            Buffer& operator >> ( sf::Int16& i );
            Buffer& operator >> ( sf::Int32& i );
            template< typename T >
            Buffer& operator >> ( sf::Vector2< T >& v )
            {
                return ( * this ) >> v.x >> v.y;
            }
            Buffer& operator >> ( std::string& str );
            template< typename T >
            Buffer& operator >> ( std::vector< T >& vec )
            {
                sf::Uint32 count;
                ( * this ) >> count;
                vec.resize( count );
                for ( sf::Uint32 i = 0; i < count; ++i )
                    ( * this ) >> vec[ i ];
                
                return ( * this );
            }
            template< typename TK, typename TV >
            Buffer& operator >> ( std::map< TK, TV >& map )
            {
                map.clear();
                sf::Uint32 count;
                ( * this ) >> count;
                for ( sf::Uint32 i = 0; i < count; ++i )
                    map.insert( { readValue< TK >(), readValue< TV >() } );
                
                return ( * this );
            }
            
            Buffer& operator << ( bool b );
            Buffer& operator << ( sf::Uint8 i );
            Buffer& operator << ( sf::Uint16 i );
            Buffer& operator << ( sf::Uint32 i );
            Buffer& operator << ( sf::Int8 i );
            Buffer& operator << ( sf::Int16 i );
            Buffer& operator << ( sf::Int32 i );
            template< typename T >
            Buffer& operator << ( sf::Vector2< T > v )
            {
                return ( * this ) << v.x << v.y;
            }
            Buffer& operator << ( const std::string& str );
            template< typename T >
            Buffer& operator << ( const std::vector< T >& vec )
            {
                sf::Uint32 count = static_cast< sf::Uint32 >( vec.size() );
                ( * this ) << count;
                for ( sf::Uint32 i = 0; i < count; ++i )
                    ( * this ) << vec[ i ];
                
                return ( * this );
            }
            template< typename TK, typename TV >
            Buffer& operator << ( const std::map< TK, TV >& map )
            {
                ( * this ) << static_cast< sf::Uint32 >( map.size() );
                for ( const auto& pair : map )
                    ( * this ) << pair.first << pair.second;
                
                return ( * this );
            }
            
            std::string data() const;
            
        private:
            std::stringstream ss;
            
            template< typename T >
            inline T readValue()
            {
                T t;
                ( * this ) >> t;
                return t;
            }
    };
}

#endif // NET_BUFFER_HPP
