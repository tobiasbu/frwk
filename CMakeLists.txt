cmake_minimum_required(VERSION 3.9)

# Project Name
project (
		purpurina
		VERSION 0.0.1
		DESCRIPTION "Purpurina Game Engine"
		LANGUAGES CXX
)

# Include the CMake Configuration and Utils file
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Utils.cmake)


# we use the paths from the cmake GNUInstallDirs module as defaults
# you can override these if you like
# https://cmake.org/cmake/help/v3.0/module/GNUInstallDirs.html
include(GNUInstallDirs)


# On Windows, should generate static or dynamic libraries
if(PURPURINA_OS_WINDOWS)

endif()

# Set paths for source files
set(PURPURINA_PACKAGES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/purpurina")

add_subdirectory(${PURPURINA_PACKAGES_DIR})

# Get Headers
# file(GLOB PURPURINA_HEADERS RELATIVE ${PROJECT_SOURCE_DIR} "${PURPURINA_INCLUDES_PATH}/*")

# add_library(Purpurina SHARED ${PURPURINA_HEADERS})

# C++ standrad libraries
# set_target_properties(Purpurina PROPERTIES LINKER_LANGUAGE CXX)

# set_target_properties(PurpurinaCore
#    PROPERTIES
#    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
# )

# file(GLOB_RECURSE PURPURINA_CORE_INCLUDES
#	LIST_DIRECTORIES false
#	"${PURPURINA_CORE_PATH}/include/*.hpp"
# )

# file(GLOB_RECURSE PURPURINA_CORE_SOURCES
#	LIST_DIRECTORIES false
#	"${PURPURINA_CORE_PATH}/src/*.cpp"
# )

# include_directories(${PURPURINA_CORE_INCLUDES})



# Public API
# set_target_properties(mylib PROPERTIES PUBLIC_HEADER include/mylib.h)


export_targets()
