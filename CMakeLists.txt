# Copyright 2020 <Shumeev Ilja (Kam1runetzLabs) notsoserious2017@gmail.com>

cmake_minimum_required(VERSION 3.4)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_COVERAGE "Build coverage" OFF)

set(
        HUNTER_CACHE_SERVERS
        "https://github.com/bmstu-iu8-cpp-sem-3/hunter-cache"
        CACHE STRING "Default cache server"
)

include("tools/gate/cmake/HunterGate.cmake")

HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.218.tar.gz"
        SHA1 "9a3594a61227967fb92159339ba326701b287b19"
)


project(cache)
string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")
string(APPEND CMAKE_CXX_FLAGS " -O0")

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

add_library(cache STATIC
        include/config.hpp sources/Experiment.cpp
        include/TravelOrders/TravelOrder.hpp
        include/TravelOrders/DirectTravelOrder.hpp
        sources/TravelOrders/DirectTravelOrder.cpp
        include/TravelOrders/ReverseTravelOrder.hpp
        sources/TravelOrders/ReverseTravelOrder.cpp
        include/TravelOrders/RandomTravelOrder.hpp
        sources/TravelOrders/RandomTravelOrder.cpp
        include/Experiment.hpp
        include/ExperimentsScheduler.hpp
        sources/ExperimentsScheduler.cpp
        include/ExperimentsCreator.hpp
        include/DefaultExperimentsCreator.hpp
        sources/DefaultExperimentsCreator.cpp
        include/ResultsPrinter.hpp
        include/DefaultPrinter.hpp
        sources/DefaultPrinter.cpp)
add_executable(tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.cpp
        )

target_include_directories(cache
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        )
target_include_directories(tests
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        )
target_link_libraries(tests GTest::main cache)

enable_testing()
add_test(NAME unit_tests COMMAND tests)

if (BUILD_COVERAGE)
    set(ENABLE_COVERAGE ON CACHE BOOL "Enable coverage build." FORCE)
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
    find_package(codecov)
    add_coverage(cache)
    add_coverage(tests)
    list(APPEND LCOV_REMOVE_PATTERNS "'${PROJECT_SOURCE_DIR}/tests/*'")
    coverage_evaluate()
endif ()
