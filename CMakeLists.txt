# To execute the cmake build: 
#   cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
#   cmake --build build
#
# For 'static' cmake build use:
#   cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF
#   cmake --build build
#
cmake_minimum_required(VERSION 3.20)
message(STATUS "CMake version is: ${CMAKE_VERSION}")
set (CMAKE_DEBUG_FIND_MODE=0)

# required before 'project' below - detects and uses 'vcpkg' if available.
# to test CMake 'FetchContent' use: 'unset VCPKG_ROOT'
message(NOTICE "Looking for 'vcpkg' install")
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  message(STATUS "Using 'vcpkg' found at: $ENV{VCPKG_ROOT}")
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
      CACHE STRING "")
  set(VCPKG_LIBRARY_LINKAGE static)
  message(STATUS "'vcpkg' static build set")
  # below needed as 'vcpkg.json' versions feature is experimental currently
  set(VCPKG_FEATURE_FLAGS "versions")
  message(STATUS "'vcpkg' versions feature enabled")
else ()
  message(STATUS "'vcpkg' not found - fallback to CMake 'FetchContent'")
endif()

project(get-uuid)

# configure C++ standard to build with
set(CMAKE_CXX_STANDARD 20)
# generate a 'compile_commands.json' for editor support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# add location for built binary application file
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
# If needed - installs dlls in the same directory as the executable on Windows
if(WIN32)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()
message(NOTICE "Final application (binary) files are output to: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
# add list of c++ source code files to ${SOURCES}
file(GLOB SOURCES "./src/*.cc")

# cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
message(NOTICE "Checking if 'Debug' or 'Release' build requested")
if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG=1)
    add_definitions(-DNDEBUG)
    message(STATUS "CMake build as 'Debug' enabled")
else ()
    message(STATUS "CMake build as 'Release' enabled")
endif()

# Use static library build
# to set equivalent of build flag: -DBUILD_SHARED_LIBS=OFF)
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)

# fix '-static' compile error
IF(APPLE)
    # Fix linking on 10.14+. See https://stackoverflow.com/questions/54068035
    LINK_DIRECTORIES(/usr/local/lib)
ENDIF()

# add flag to hide depreciation code warnings
#add_definitions(-DAPPROVAL_TESTS_HIDE_DEPRECATED_CODE=1)

# add additional compiler options (NB build fails with: '-Werror')
# '-Qunused-arguments' is clang only option and breaks GCC builds
# Silence 'zlib' build warnings: -Qunused-arguments
# Silence 'curl' build warnings: -Wno-deprecated
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -pedantic -Qunused-arguments -Wno-deprecated -static)
else()
    add_compile_options(-Wall -Wextra -pedantic -Wno-deprecated -static)
endif()

add_executable(get-uuid ${SOURCES})

# Use 'vcpkg' if available
if (DEFINED ENV{VCPKG_ROOT} AND DEFINED CMAKE_TOOLCHAIN_FILE)
    find_package(fmt CONFIG REQUIRED)
    find_package(argparse CONFIG REQUIRED)
else ()
    set(FETCHCONTENT_UPDATES_DISCONNECTED ON CACHE BOOL "")
    include(FetchContent)

    # Add libraries to be fetched below:
    FetchContent_Declare(
      fmt
      GIT_REPOSITORY https://github.com/fmtlib/fmt.git
      GIT_TAG 8.1.1)
    FetchContent_MakeAvailable(fmt)

    FetchContent_Declare(
      argparse
      GIT_REPOSITORY https://github.com/p-ranav/argparse.git
      GIT_TAG v2.2)
    FetchContent_MakeAvailable(argparse)

endif()

target_link_libraries(get-uuid PRIVATE fmt::fmt argparse::argparse)
