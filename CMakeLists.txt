cmake_minimum_required(VERSION 3.15)
project(ztmapi_core)
set(CMAKE_CXX_STANDARD 14)


find_package(PythonInterp)
find_package(Boost COMPONENTS regex locale python${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR})
find_package(PythonInterp 3)
find_package(PythonLibs 3 REQUIRED)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
file(GLOB ztmapi_SRC "src/*")

include_directories(${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS} include/)
link_libraries(curl curlpp ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
python_add_module(ztmapi_core main.cpp ${ztmapi_SRC})