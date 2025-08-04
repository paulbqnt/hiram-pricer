cmake_minimum_required(VERSION 3.16)
project(hiram_pricing_engine)

set(CMAKE_CXX_STANDARD 20)

# Use system-installed Boost
find_package(Boost REQUIRED COMPONENTS system)

# Use system-installed nlohmann_json
find_package(nlohmann_json REQUIRED)

# Collect sources
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        src/*.cpp
        main/*.cpp
)

add_executable(hiram_pricing_engine ${SOURCES})

# Link against Boost and nlohmann_json (system libraries)
target_include_directories(hiram_pricing_engine PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(hiram_pricing_engine PRIVATE ${Boost_LIBRARIES} nlohmann_json::nlohmann_json)
