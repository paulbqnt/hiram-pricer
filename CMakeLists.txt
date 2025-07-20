cmake_minimum_required(VERSION 3.31)
project(hiram_pricing_engine)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost REQUIRED COMPONENTS system)

# Collect sources
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        src/*.cpp
        main/*.cpp
)

add_executable(hiram_pricing_engine ${SOURCES})

target_include_directories(hiram_pricing_engine PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(hiram_pricing_engine PRIVATE Boost::system)
