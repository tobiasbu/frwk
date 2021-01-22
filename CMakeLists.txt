cmake_minimum_required(VERSION 3.9)

set (CMAKE_CXX_STANDARD 11)

# Project Name
project (purpurina
		VERSION 0.0.1
		DESCRIPTION "Purpurina Game Engine"
		LANGUAGES CXX)


# Include the CMake Configuration and Utils files
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/macros.cmake)

# we use the paths from the cmake GNUInstallDirs module as defaults
# you can override these if you like
# https://cmake.org/cmake/help/v3.0/module/GNUInstallDirs.html
include(GNUInstallDirs)

# enable folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")

# Set paths for purpurina packages files
set(PURPURINA_SRC "${PROJECT_SOURCE_DIR}/src/purpur")
set(PURPURINA_INC "${PROJECT_SOURCE_DIR}/include/purpur")
set(PURPURINA_EXTLIBS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty")

#############################################
####		    COMMON OPTIONS			 ####
#############################################

# Define BUILD_SHARED_LIBS property
option(BUILD_SHARED_LIBS "TRUE = Build Purpurina as shared libraries; FALSE = Build as static libraries" TRUE)

# Should build sandox examples?
option(PURPURINA_SANDBOX "TRUE = Build the Purpurina Sandbox; FALSE = Don't build Sandbox" TRUE)

# [WINDOWS] Make a multi options for executables
if(PURPURINA_OS_WINDOWS AND BUILD_SHARED_LIBS AND PURPURINA_SANDBOX)
	ppr_multi_options(
		PURPURINA_SANDBOX_POSTCOMMAND
		"exe_to_bin"
		"exe_to_bin;bin_to_exe"
"Defines post build command for executables.
This is necessary to link executables with dynamic libraries.
 * exe_to_bin = Build executables in the same folder of libraries
 * bin_to_exe = Make a copy of libraries to the executable folders.")
endif()

#############################################
####		      OS OPTIONS			 ####
#############################################

# [WINDOWS] Should generate static or dynamic libraries
if(PURPURINA_OS_WINDOWS)
	option(PURPURNA_STATIC_STDLIBS "TRUE to statically link to the standard libraries, FALSE to use them as DLLs" FALSE)

	# the following combination of flags is not valid
	if (BUILD_SHARED_LIBS AND PURPURINA_STATIC_STDLIBS)
		message(FATAL_ERROR "Can not use BUILD_SHARED_LIBS and PURPURINA_STATIC_STDLIBS together.")
 	endif()

  	# for VC++, set globally compiler flags
	if(PURPURINA_MSVC AND PURPURINA_STATIC_STDLIBS)
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
if(PURPURINA_OS_MACOSX)
	set(XCODE_TEMPLATES_ARCH "\$(NATIVE_ARCH_ACTUAL)")
endif()

#############################################
####		     ADD PACAKGES 			 ####
#############################################

add_subdirectory(${PURPURINA_SRC})

# Sandbox
if (PURPURINA_SANDBOX)
	add_subdirectory("${PROJECT_SOURCE_DIR}/sandbox")
endif()


#############################################
####		       INSTALL    			 ####
#############################################

# Install all packages includes
file(GLOB PACKAGE_PATHS "${PURPURINA_INCLUDE}/**")
foreach(ITEM ${PACKAGE_PATHS})
	if(IS_DIRECTORY ${ITEM})
		list( APPEND DIRS_TO_DEPLOY "${ITEM}" )
    endif()
endforeach()

install(DIRECTORY ${DIRS_TO_DEPLOY}
        DESTINATION include
        COMPONENT devel
        FILES_MATCHING PATTERN "*.hpp" PATTERN "*.inl")

ppr_export_targets()
