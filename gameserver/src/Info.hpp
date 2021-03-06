#ifndef INFO_HPP
#define INFO_HPP

#include <cstddef>
#include <SFML/Config.hpp>

constexpr sf::Uint16 PROTOCOL_VERSION = 0;
constexpr const char* GAME_IP = "localhost";
constexpr sf::Uint16 GAME_PORT = 3151;

constexpr std::size_t RECV_BUFFER_SIZE = 256;
constexpr std::size_t RECV_BUFFER_REFRESH = 1024;

#endif // INFO_HPP
