cmake_minimum_required(VERSION 3.24)
project(MersulTrenurilorOOP)

set(CMAKE_CXX_STANDARD 23)

add_executable(MersulTrenurilorOOP src/Server.cpp src/Client.cpp src/DatabaseHandler.cpp src/DatabaseHandler.h src/Login.cpp src/Login.h src/Register.cpp src/Register.h lib/sha256.cpp)
