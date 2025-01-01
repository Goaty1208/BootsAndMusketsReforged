cmake_minimum_required(VERSION 3.12)
project(bootsAndMuskets)

# Set the version of Raylib required
set(RAYLIB_VERSION 5.0)

# Check if the platform is Windows or Linux
if (WIN32)
    set(OS_PLATFORM "Windows")
else()
    set(OS_PLATFORM "Linux")
endif()

message(STATUS "Compiling for ${OS_PLATFORM}")

# Allow setting the build type, default to Debug for development
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type (Debug/Release/RelWithDebInfo/MinSizeRel)" FORCE)
endif()

# Generate compile_commands.json for development tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include external dependencies like Raylib
include(FetchContent)
FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
)
FetchContent_MakeAvailable(raylib)

# Fetch nlohmann/json
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2 # Use a specific version; you can update this as needed
)
FetchContent_MakeAvailable(json)

# Ensure Raylib examples are not built
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Set output directories for the compiled binary
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/debug)

# Add all source files recursively from the src/ directory
# This will automatically pick up any `.cpp` and `.h` files in the `src/` directory
file(GLOB_RECURSE SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/*.h
)

# Add executable for the project with the source files
add_executable(${PROJECT_NAME} ${SOURCES})

# Set the working directory to the location of the executable (useful for debugging)
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

# Include source directory for header files
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Link Raylib and nlohmann/json to the project
target_link_libraries(${PROJECT_NAME} PRIVATE raylib nlohmann_json::nlohmann_json)

# Add compiler flags
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /ZI) # Windows, Visual Studio
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /ZI")
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Wwrite-strings -Wmissing-field-initializers -g) # Linux, GCC/Clang
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
endif()

# Add defines based on build type
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG)
else()
    target_compile_definitions(${PROJECT_NAME} PRIVATE RELEASE)
endif()

# Platform-specific configurations
if (WIN32)
    # Windows-specific libraries
    target_link_libraries(${PROJECT_NAME} PRIVATE winmm)
elseif (APPLE)
    # MacOS-specific libraries
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
elseif (UNIX)
    # Linux-specific libraries
    target_link_libraries(${PROJECT_NAME} PRIVATE pthread dl m)
endif()

# Web platform configurations (Emscripten)
if (CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
    target_link_options(${PROJECT_NAME} PRIVATE -sUSE_GLFW=3 --preload-file resources)
endif()
