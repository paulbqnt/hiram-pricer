cmake_minimum_required(VERSION 3.16)
project(hiram_pricer LANGUAGES CXX)

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

# Collect main sources (from main directory)
file(GLOB_RECURSE MAIN_SOURCES CONFIGURE_DEPENDS
        main/*.cpp
)

# Add all sources
add_executable(hiram_pricer
        ${MAIN_SOURCES}
        ${SOURCES}
        src/main.cpp
        src/core/pricing/pricing_engine.cpp
        src/core/pricing/pricing_result.cpp
        src/core/models/analytical/black_scholes_analytical.cpp
        src/core/enums/model_method_pair.cpp
        src/core/enums/model_method_pair.cpp  # ADD THIS LINE
)

# Include directories
target_include_directories(hiram_pricer
        PRIVATE
        ${Boost_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/src
)

# Link libraries
target_link_libraries(hiram_pricer
        PRIVATE
        ${Boost_LIBRARIES}
        nlohmann_json::nlohmann_json
)
