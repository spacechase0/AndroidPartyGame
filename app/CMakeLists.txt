# Sets the minimum version of CMake required to build the native
# library. You should either keep the default value or only pass a
# value of 3.4.0 or lower.

cmake_minimum_required(VERSION 3.4.1)

#set(SFML_ROOT ${ANDROID_NDK}/sources/sfml)
#FIND_PACKAGE(SFML COMPONENTS system window graphics audio network main activity)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -include Info.hpp -frtti -fexceptions")

add_library( kingdomparty-native SHARED
src/main/cpp/client/Client.cpp
src/main/cpp/client/lobby/NetStage.cpp
src/main/cpp/client/main.cpp
src/main/cpp/client/match/Match.cpp
src/main/cpp/client/match/NetStage.cpp
src/main/cpp/client/prelogin/NetStage.cpp
src/main/cpp/game/MapData.cpp
src/main/cpp/game/MatchData.cpp
src/main/cpp/game/PlayerData.cpp
src/main/cpp/game/UserData.cpp
src/main/cpp/net/Buffer.cpp
src/main/cpp/net/Connection.cpp
src/main/cpp/net/lobby/CreateMatchPacket.cpp
src/main/cpp/net/lobby/JoinMatchPacket.cpp
src/main/cpp/net/lobby/MatchListPacket.cpp
src/main/cpp/net/lobby/MatchStatusPacket.cpp
src/main/cpp/net/lobby/NetStage.cpp
src/main/cpp/net/lobby/RequestMatchListPacket.cpp
src/main/cpp/net/match/DiceRollPacket.cpp
src/main/cpp/net/match/MatchStartDataPacket.cpp
src/main/cpp/net/match/MinigameEndPacket.cpp
src/main/cpp/net/match/MinigameInputDataPacket.cpp
src/main/cpp/net/match/MinigameStartPacket.cpp
src/main/cpp/net/match/MinigameStateDataPacket.cpp
src/main/cpp/net/match/NetStage.cpp
src/main/cpp/net/match/TurnOrderPacket.cpp
src/main/cpp/net/NetStage.cpp
src/main/cpp/net/Packet.cpp
src/main/cpp/net/prelogin/LoginPacket.cpp
src/main/cpp/net/prelogin/LoginStatusPacket.cpp
src/main/cpp/net/prelogin/NetStage.cpp
src/main/cpp/net/prelogin/ProtocolVersionPacket.cpp
src/main/cpp/net/prelogin/RegisterPacket.cpp
src/main/cpp/util/Base64.cpp
src/main/cpp/util/Crc32.cpp
src/main/cpp/util/Endian.cpp
src/main/cpp/util/File.cpp
src/main/cpp/util/Logger.cpp
src/main/cpp/util/Md5.cpp
src/main/cpp/util/String.cpp
src/main/cpp/Util.cpp
)
include_directories(src/main/cpp)
find_library(sfsys sfml-system)
#find_library(sfwin sfml-window)
#find_library(sfgraph sfml-graphics)
#find_library(sfaud sfml-audio)
#find_library(sfnet sfml-network)
#find_library(sfmain sfml-main)
#find_library(sfact sfml-activity)

set(SF ${ANDROID_NDK}/sources/sfml)
set(SFL ${SF}/lib/${ANDROID_NDK_ABI_NAME})

include_directories(src/main/cpp)
include_directories(${SF}/include)

target_link_libraries( kingdomparty-native ${SFL}/libsfml-main.a ${SFL}/libsfml-system.so ${SFL}/libsfml-window.so ${SFL}/libsfml-graphics.so ${SFL}/libsfml-audio.so ${SFL}/libsfml-network.so ${SFL}/libsfml-activity.so )
#target_link_libraries( kingdomparty-native ${sfwin} )
#target_link_libraries( kingdomparty-native ${sfgraph} )
#target_link_libraries( kingdomparty-native ${sfaud} )
#target_link_libraries( kingdomparty-native ${sfnet} )
#target_link_libraries( kingdomparty-native ${sfmain} )
#target_link_libraries( kingdomparty-native ${sfact} )

