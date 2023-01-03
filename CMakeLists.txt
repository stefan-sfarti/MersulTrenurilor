cmake_minimum_required(VERSION 3.24)
project(MersulTrenurilor)

set(CMAKE_CXX_STANDARD 17)
set( CMAKE_BUILD_TYPE Debug )
include_directories(/usr/include/mysql)

add_executable (client client.cpp)
add_executable (server server.cpp DbCon.cpp DbCon.h Thread.cpp Thread.h)


target_link_libraries ( server pthread mysqlclient)
