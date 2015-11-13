cmake_minimum_required(VERSION 2.8.11)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules)
project(eventalertd C CXX)

#build type
set(CMAKE_BUILD_TYPE Debug)
message("Build Type: ${CMAKE_BUILD_TYPE}")

# output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMKAE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# pthreads
find_package(Threads REQUIRED)

# BOOST
set(BOOST_ROOT $ENV{BOOST_DIR})
set(Boost_USE_STATIC_LIBS    OFF)
set(Boost_USE_MULTITHREADED   ON)
set(Boost_USE_STATIC_RUNTIME OFF)
add_definitions(-DBOOST_LOG_DYN_LINK)
find_package(Boost 1.55.0 REQUIRED COMPONENTS log log_setup filesystem thread date_time program_options system)
include_directories(${Boost_INCLUDE_DIRS})

# compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")

# add source directories
add_subdirectory(src)
#add_subdirectory(tst)