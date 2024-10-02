cmake_minimum_required(VERSION 3.20)

project(Tcp-Server)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

add_executable(client ${SRC_DIR}/client.cpp)

file(GLOB SERVER_SOURCES ${SRC_DIR}/*.cpp)
list(REMOVE_ITEM SERVER_SOURCES ${SRC_DIR}/client.cpp)
add_executable(server ${SERVER_SOURCES})
target_link_libraries(server PRIVATE Threads::Threads)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
