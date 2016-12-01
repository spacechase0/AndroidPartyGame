#ifndef UTIL_HPP
#define UTIL_HPP

#include <fstream>
#include <string>
#include <vector>

std::ifstream&& getResourceFile( const std::string& name );
std::vector< std::string > parseCommand( const std::string& str );

#endif // UTIL_HPP
