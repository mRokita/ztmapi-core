cmake_minimum_required(VERSION 3.10)
include(FindPkgConfig)
project(ztmapi_core)
set(CMAKE_CXX_STANDARD 14)

find_package(PythonInterp 3 REQUIRED)

if($ENV{UBUNTU})
    set(BOOST_PYTHONLIB python-py${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR})
else()
    set(BOOST_PYTHONLIB python${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR})
endif()
find_package(Boost COMPONENTS regex locale ${BOOST_PYTHONLIB} REQUIRED)
find_package(PythonLibs 3 REQUIRED)
pkg_check_modules(CURLPP REQUIRED curlpp)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/setup.py
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
file(GLOB ztmapi_SRC "src/*")

include_directories(${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS} include/ tests/catch2)
link_libraries(curl curlpp ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
python_add_module(ztmapi_core main.cpp ${ztmapi_SRC})
install(CODE "execute_process(COMMAND pip install .)")

SET(CMAKE_EXE_LINKER_FLAGS -licuuc)

add_executable(run_tests tests/test.cpp ${ztmapi_SRC})