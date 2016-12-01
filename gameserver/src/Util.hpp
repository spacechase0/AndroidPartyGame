#ifndef UTIL_HPP
#define UTIL_HPP

#include <fstream>
#include <string>
#include <vector>

void loadResourceFile( std::ifstream& file, const std::string& name );
std::vector< std::string > parseCommand( const std::string& str );

#endif // UTIL_HPP
