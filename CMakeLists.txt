cmake_minimum_required(VERSION 3.16)
project(hiram_pricing_engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use system-installed Boost
find_package(Boost REQUIRED COMPONENTS system)

# Use system-installed nlohmann_json
find_package(nlohmann_json REQUIRED)

# Collect sources from src directory
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        src/*.cpp
)

# Add main.cpp separately
add_executable(hiram_pricing_engine
        main.cpp
        ${SOURCES}
)

# Include directories
target_include_directories(hiram_pricing_engine
        PRIVATE
        ${Boost_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/src
)

# Link libraries
target_link_libraries(hiram_pricing_engine
        PRIVATE
        ${Boost_LIBRARIES}
        nlohmann_json::nlohmann_json
)