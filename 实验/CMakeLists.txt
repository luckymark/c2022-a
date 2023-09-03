cmake_minimum_required(VERSION 3.24)
project(ChessAI)

set(CMAKE_CXX_STANDARD 17)

set(EasyX_INC "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Auxiliary\\VS\\include") # 你的include地址
set(EasyX_LINK "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Auxiliary\\VS\\lib\\x64") # 找与自己的环境配置对应的版本
include_directories(${EasyX_INC})
link_directories(${EasyX_LINK})
#在lib对应的文件夹里面找lib文件（一般只有EasyXa和EasyXw这两个，进行链接）
link_libraries(EasyXa)
link_libraries(EasyXw)

add_executable(ChessAI resource.h Chess.rc Board.cpp Board.h role.cpp role.h point.h score.h point.cpp GUI.cpp GUI.h AI.cpp AI.h Chess.h Chess.cpp)
