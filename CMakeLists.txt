cmake_minimum_required(VERSION 3.15)
project(ztmapi_core)

set(CMAKE_CXX_STANDARD 14)
add_executable(ztmapi_core main.cpp)

target_link_libraries(ztmapi_core curl)
target_link_libraries(ztmapi_core curlpp)