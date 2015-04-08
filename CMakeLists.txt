cmake_minimum_required(VERSION 2.8.4)
project(AlfaTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated -ansi")

set(Boost_USE_STATIC_LIBS        OFF) # only find static libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME     OFF)

find_package(Boost 1.41 COMPONENTS system graph test REQUIRED)

add_executable(AlfaTest main.cpp)

add_executable(AlfaUnitTest Graph.ut.cpp)

target_link_libraries (AlfaUnitTest boost_unit_test_framework-mt)

enable_testing ()
add_test (AlfaUnitTest AlfaUnitTest)
