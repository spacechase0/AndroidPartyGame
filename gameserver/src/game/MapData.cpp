#include "game/MapData.hpp"

#include <cctype>
#include <util/String.hpp>

#include "game/TileData.hpp"
#include "net/Buffer.hpp"
#include "Util.hpp"

namespace
{
    net::Buffer& operator >> ( net::Buffer& buffer, game::TileData& tile )
    {
        sf::Uint8 type;
        buffer >> type;
        tile.type = static_cast< game::TileData::Type >( type );
        buffer >> tile.hasStar >> tile.next;
        return buffer;
    }
    
    net::Buffer& operator << ( net::Buffer& buffer, const game::TileData& tile )
    {
        buffer << static_cast< sf::Uint8 >( tile.type ) << tile.hasStar << tile.next;
        return buffer;
    }
    
    std::string trim( const std::string& str )
    {
        std::size_t beg = 0;
        for ( ; beg < str.length(); ++beg )
            if ( !std::isspace( str[ beg ] ) )
                break;
        
        std::size_t end = str.length() - 1;
        for ( ; end > 0; --end )
            if ( !std::isspace( str[ end ] ) )
                break;
        
        if ( end <= beg ) return "";
        return str.substr( beg, end - beg );
    }
}

namespace game
{
    bool MapData::load( const std::string& filename )
    {
        std::ifstream file;
        loadResourceFile( file, filename );
        if ( !file ) return false;
        
        std::getline( file, name );
        file >> size.x >> size.y;
        std::string tmp; std::getline( file, tmp );
        
        tiles.clear();
        tiles.resize( size.x * size.y );
        namedTiles.clear();
        start = sf::Vector2u( 0xFFFFFFFF, 0xFFFFFFFF );
        
        std::vector< std::pair< sf::Vector2u, std::vector< std::string > > > toSetNext;
        TileData* prevTile = nullptr;
        bool tileMode = false;
        while ( true )
        {
            std::string line;
            std::getline( file, line );
            if ( !file ) break;
            
            line = trim( line );
            if ( line == "" || line[ 0 ] == '#' ) continue;
            
            if ( tileMode )
            {
                auto tokens = util::tokenize( line, "," );
                if ( tokens.size() < 3 ) continue;
                
                TileData tile;
                sf::Vector2u pos( util::fromString< sf::Uint32 >( tokens[ 0 ] ), util::fromString< sf::Uint32 >( tokens[ 1 ] ) );
                
                char type = tokens[ 2 ][ 0 ];
                switch ( type )
                {
                    case 'b': tile.type = TileData::Type::Blue;    break;
                    case 'r': tile.type = TileData::Type::Red;     break;
                    case 's': tile.type = TileData::Type::Special; break;
                }
                
                if ( prevTile )
                {
                    prevTile->next.push_back( pos );
                }
                prevTile = nullptr;
                
                if ( tokens.size() >= 4 )
                {
                    auto attrs = util::tokenize( tokens[ 3 ], " " );
                    for ( const auto& attr : attrs )
                    {
                        std::size_t eq = attr.find( '=' );
                        std::string name = attr.substr( 0, eq );
                        std::string val = eq != std::string::npos ? attr.substr( eq + 1 ) : "";
                        
                        if ( name == "start" )
                            start = pos;
                        else if ( name == "name" )
                            namedTiles[ val ] = pos;
                        else if ( name == "next" )
                            toSetNext.push_back( { pos, util::tokenize( val, "/" ) } );
                    }
                }
                
                tiles[ tileIndex( pos.x, pos.y ) ] = tile;
            }
            else
            {
                if ( line == "TILES" )
                    tileMode = true;
            }
        }
        
        for ( const auto& toSet : toSetNext )
        {
            TileData& tile = tiles[ tileIndex( toSet.first.x, toSet.first.y ) ];
            for ( auto nextName : toSet.second )
                tile.next.push_back( namedTiles[ nextName ] );
        }
        
        return true;
    }
    
    std::string MapData::getName() const
    {
        return name;
    }
    sf::Vector2u MapData::getSize() const
    {
        return size;
    }
    
    TileData& MapData::getTile( unsigned int x, unsigned int y )
    {
        return tiles[ tileIndex( x, y ) ];
    }
    
    const TileData& MapData::getTile( unsigned int x, unsigned int y ) const
    {
        return tiles[ tileIndex( x, y ) ];
    }
    
    sf::Vector2u MapData::getStart() const
    {
        return start;
    }
    
    sf::Vector2u MapData::findNamedTile( const std::string& name ) const
    {
        auto it = namedTiles.find( name );
        if ( it == namedTiles.end() )
        {
            return sf::Vector2u( 0xFFFFFFFF, 0xFFFFFFFF );
        }
        return it->second;
    }
    
    net::Buffer& operator >> ( net::Buffer& buffer, MapData& map )
    {
        buffer >> map.name >> map.size >> map.tiles >> map.namedTiles >> map.start;
        return buffer;
    }
    
    net::Buffer& operator << ( net::Buffer& buffer, const MapData& map )
    {
        buffer << map.name << map.size << map.tiles << map.namedTiles << map.start;
        return buffer;
    }
}
