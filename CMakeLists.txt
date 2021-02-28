cmake_minimum_required(VERSION 3.9)

# Add common functions
include(cmake/commons.cmake)

# The options and cofiguration defined here must come
# before CMake configure toolchains and project

# Determine build type
ct_option(CMAKE_BUILD_TYPE "Debug" STRING "Choose the type of build (Debug or Release)")

if(NOT CMAKE_OSX_ARCHITECTURES)
    set(CMAKE_OSX_ARCHITECTURES "x86_64" CACHE STRING "macOS architecture to build; 64-bit is expected" FORCE)
endif()

# Project
project (chronotrix_frwk
		VERSION 0.0.1
		DESCRIPTION "Chronotrix Framework"
		LANGUAGES C CXX)

include(CMakeDependentOption)
include(GNUInstallDirs)

#############################################
####             BASE CONFIG             ####
#############################################

# C/C++ version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Project config
set_property(GLOBAL PROPERTY USE_FOLDERS ON) # enable folders
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")

# Include the CMake Configuration and helpers files
include(cmake/config.cmake)
include(cmake/helpers.cmake)

# Set paths for chronotrix packages files
set(CT_FRWK_PATH "${PROJECT_SOURCE_DIR}")
set(CT_SRC "${CT_FRWK_PATH}/src/ct")
set(CT_INC "${CT_FRWK_PATH}/include/ct")
set(CMAKE_MODULE_PATH "${CT_FRWK_PATH}/cmake/modules")
set(CT_EXTLIBS_PATH "${CT_FRWK_PATH}/thirdparty")
set(CT_HEADER_GROUP "Header Files")
set(CT_SOURCE_GROUP "Source Files")

#############################################
####              OPTIONS               ####
#############################################

# Define BUILD_SHARED_LIBS property
ct_option(BUILD_SHARED_LIBS TRUE BOOL "TRUE = build Chronotrix as shared libraries. FALSE = build as static libraries")

# Build examples
ct_option(CT_EXAMPLES TRUE BOOL "TRUE = Build the Chronotrix examples. FALSE = Don't build examples")

# Build docs
ct_option(CT_DOCS FALSE BOOL "TRUE = generate the API documentation. FALSE = ignore it")

# Build tests
ct_option(CT_TESTS FALSE BOOL "Build tests")

# Check for clang-tidy
set(ENABLE_CLANG_TIDY TRUE CACHE BOOL "Add clang-tidy automatically to builds")
if (ENABLE_CLANG_TIDY)

	find_program(CLANG_TIDY_EXE NAMES "clang-tidy" PATHS /usr/local/opt/llvm/bin /usr/local/bin)
	if (CLANG_TIDY_EXE)
		set(CMAKE_CXX_CLANG_TIDY "clang-tidy" CACHE STRING "" FORCE)
		message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
	else()
		set(CMAKE_CXX_CLANG_TIDY "" CACHE STRING "" FORCE) # delete it
		message(WARNING "clang-tidy not found! Skipping")
	endif()
endif()


# [WINDOWS] Make a multi options for executables
if(CT_OS_WINDOWS AND BUILD_SHARED_LIBS AND CT_EXAMPLES)
	ct_multi_options(
		CT_EXAMPLES_POSTCOMMAND
		"exe_to_bin"
		"exe_to_bin;bin_to_exe"
		"Defines post build command for executables.
		This is necessary to link executables with dynamic libraries.
		* exe_to_bin = Build executables in the same folder of libraries
		* bin_to_exe = Make a copy of libraries to the executable folders.")
endif()


#############################################
####              OS CONFIG              ####
#############################################

# [WINDOWS] Should generate static or dynamic libraries
if(CT_OS_WINDOWS)
	option(CT_STATIC_STDLIBS "TRUE to statically link to the standard libraries, FALSE to use them as DLLs" FALSE)

	# the following combination of flags is not valid
	if (BUILD_SHARED_LIBS AND CT_STATIC_STDLIBS)
		message(FATAL_ERROR "Can not use BUILD_SHARED_LIBS and CT_STATIC_STDLIBS together.")
 	endif()

  	# for VC++, set globally compiler flags
	if(CT_COMPILER_MSVC AND CT_STATIC_STDLIBS)
		foreach(flag
				CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
				CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
			if(${flag} MATCHES "/MD")
				string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
			endif()
		endforeach()

		# add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
		# add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
	endif()

	# There is a bug in MSVC Community 2019 >= v16.8.4
	# does not recognize whitespace in source_group.
	# This seems to happens after the configuration from above lines.
	# So, we repest the defintions os groups again:
	if(CT_COMPILER_MSVC)
		set(CT_HEADER_GROUP "Headers Files")
		set(CT_SOURCE_GROUP "Sources Files")
	endif()

endif()

# [MACOSX] Setup
if(CT_OS_MACOSX)
	set(XCODE_TEMPLATES_ARCH "\$(NATIVE_ARCH_ACTUAL)")
endif()

#############################################
####             ADD PACAKGES            ####
#############################################

add_subdirectory(${CT_SRC})

# Examples
if (CT_EXAMPLES)
	add_subdirectory("${CT_FRWK_PATH}/examples")
endif()

# Tests
if(CT_TESTS)
	add_subdirectory("${CT_FRWK_PATH}/tests")
endif()

if(CT_DOCS)
add_subdirectory("${CT_FRWK_PATH}/docs")
endif()

#############################################
####               INSTALL               ####
#############################################

# Install all packages includes
install(DIRECTORY "${CT_INC}"
		DESTINATION include
        COMPONENT devel
        FILES_MATCHING PATTERN "*.hpp" PATTERN "*.inl")

ct_export_targets()
