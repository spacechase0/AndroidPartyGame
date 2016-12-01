#include "Util.hpp"

void loadResourceFile( std::ifstream& file, const std::string& name )
{
    file.open( name );
}

std::vector< std::string > parseCommand( const std::string& str )
{
    std::vector< std::string > ret;
    
    bool quote = false;
    bool escape = false;
    std::string curr = "";
    for ( char c : str )
    {
        if ( escape )
        {
            curr += c;
            escape = false;
            continue;
        }
        
        if ( c == '\\' )
            escape = true;
        else if ( c == '"' )
            quote = !quote;
        else if ( c == ' ' && !quote )
        {
            ret.push_back( std::move( curr ) );
            curr = "";
        }
        else
            curr += c;
    }
    if ( curr.length() > 0 )
        ret.push_back( curr );
    
    return ret;
}
