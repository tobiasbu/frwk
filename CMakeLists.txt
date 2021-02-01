cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(NOT CMAKE_OSX_ARCHITECTURES)
    set(CMAKE_OSX_ARCHITECTURES "x86_64" CACHE STRING "macOS architecture to build; 64-bit is expected" FORCE)
endif()

# Project Name
project (purpurina
		VERSION 0.0.1
		DESCRIPTION "Purpurina Game Engine"
		LANGUAGES CXX)


include(CMakeDependentOption)
# we use the paths from the cmake GNUInstallDirs module as defaults
# you can override these if you like
# https://cmake.org/cmake/help/v3.0/module/GNUInstallDirs.html
include(GNUInstallDirs)

# Include the CMake Configuration and Utils files
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/helpers.cmake)

# enable folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")

# Set paths for purpurina packages files
set(PURPUR_FRWK_PATH "${PROJECT_SOURCE_DIR}")
set(PURPUR_SRC "${PURPUR_FRWK_PATH}/src/purpur")
set(PURPUR_INC "${PURPUR_FRWK_PATH}/include/purpur")
set(PURPUR_EXTLIBS_PATH "${PURPUR_FRWK_PATH}/thirdparty")

#############################################
####		       OPTIONS     			 ####
#############################################

# Define BUILD_SHARED_LIBS property
option(BUILD_SHARED_LIBS "TRUE = Build Purpurina as shared libraries; FALSE = Build as static libraries" TRUE)

# Should build sandox examples?
option(PURPUR_EXAMPLES "TRUE = Build the Purpurina examples; FALSE = Don't build examples" TRUE)

# [WINDOWS] Make a multi options for executables
if(PPR_OS_WINDOWS AND BUILD_SHARED_LIBS AND PURPUR_EXAMPLES)
	ppr_multi_options(
		PURPUR_EXAMPLES_POSTCOMMAND
		"exe_to_bin"
		"exe_to_bin;bin_to_exe"
		"Defines post build command for executables.
		This is necessary to link executables with dynamic libraries.
		* exe_to_bin = Build executables in the same folder of libraries
		* bin_to_exe = Make a copy of libraries to the executable folders.")
endif()

# tests
option(PURPUR_TESTS "Build tests")

#############################################
####		      OS OPTIONS			 ####
#############################################

# [WINDOWS] Should generate static or dynamic libraries
if(PPR_OS_WINDOWS)
	option(PURPURNA_STATIC_STDLIBS "TRUE to statically link to the standard libraries, FALSE to use them as DLLs" FALSE)

	# the following combination of flags is not valid
	if (BUILD_SHARED_LIBS AND PURPUR_STATIC_STDLIBS)
		message(FATAL_ERROR "Can not use BUILD_SHARED_LIBS and PURPUR_STATIC_STDLIBS together.")
 	endif()

  	# for VC++, set globally compiler flags
	if(PPR_COMPILER_MSVC AND PURPUR_STATIC_STDLIBS)
		foreach(flag
				CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
				CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
			if(${flag} MATCHES "/MD")
				string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
			endif()
		endforeach()
	endif()
endif()

# [MACOSX] Setup
if(PPR_OS_MACOSX)
	set(XCODE_TEMPLATES_ARCH "\$(NATIVE_ARCH_ACTUAL)")
endif()

#############################################
####		     ADD PACAKGES 			 ####
#############################################

add_subdirectory(${PURPUR_SRC})

# examples
if (PURPUR_EXAMPLES)
	add_subdirectory("${PURPUR_FRWK_PATH}/examples")
endif()

# tests
if(PURPUR_TESTS)
	add_subdirectory("${PURPUR_FRWK_PATH}/tests")
endif()


#############################################
####		       INSTALL    			 ####
#############################################

# Install all packages includes
install(DIRECTORY "${PURPUR_INC}"
		DESTINATION include
        COMPONENT devel
        FILES_MATCHING PATTERN "*.hpp" PATTERN "*.inl")

ppr_export_targets()
