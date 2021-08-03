
include(CMakeParseArguments)

# ----------------------------------------------------------------------------------------------
#
# Get project major version
#
macro(get_project_version ct_ver)
	set(${ct_ver} "${${PROJECT_NAME}_VERSION_MAJOR}")
endmacro()

# ----------------------------------------------------------------------------------------------
#
# Set Xcode property
#
# @param target {TARGET}		cmake target
# @param xcode_prop {STRING}	property name
# @param xcode_value {STRING}	property value
#
macro (ct_set_xcode_prop target xcode_prop xcode_value)
    set_property (TARGET ${TARGET} PROPERTY XCODE_ATTRIBUTE_${xcode_prop} ${xcode_value})
endmacro ()

# ----------------------------------------------------------------------------------------------
#
# Add Chronotrix directory
#
# @param package_name {STRING}	cmake target name
#
function(ct_add_lib_directory package_name)
	# message("optional arguments: ${ARGN}")

    set(INCPATH ${CT_INC}/${package_name})
    set(SRCPATH ${CT_SRC}/${package_name})

    add_subdirectory(${package_name})
endfunction()

# ----------------------------------------------------------------------------------------------
#
# Add Chronotrix library
#
# @param target {TARGET}			cmake target
# @param SOURCES {STRING[]}		list of files
# @param DEPENDS? {(TARGET | STRING)[]}	optional - list of dependencies
#
macro(ct_add_library target)

	# Parse arguments
	cmake_parse_arguments(ARGS "" "" "SOURCES;DEPENDS" ${ARGN})
	if (NOT "${ARGS_UNPARSED_ARGUMENTS}" STREQUAL "" AND NOT ${ARGS_UNPARSED_ARGUMENTS} STREQUAL "LINK")
        message(FATAL_ERROR "ct_add_library: Extra unparsed arguments: ${ARGS_UNPARSED_ARGUMENTS}")
    endif()

	# Create library target
	add_library(${target} ${ARGS_SOURCES})

	# Define Export symbol
	string(REPLACE "-" "_" EXPORT_SYMBOL_NAME "${target}")
	string(TOUPPER "${EXPORT_SYMBOL_NAME}" EXPORT_SYMBOL_NAME)
	set_target_properties(${target} PROPERTIES DEFINE_SYMBOL "${EXPORT_SYMBOL_NAME}_EXPORTS")

	# Set libray output files names
	get_project_version(FK_VERSION)
	# set_target_properties(${target} PROPERTIES PREFIX "${PROJECT_NAME}_")

	if(CT_STATIC)
		set_target_properties(${target} PROPERTIES DEBUG_POSTFIX - ${FK_VERSION}-s.dev)
		set_target_properties(${target} PROPERTIES RELEASE_POSTFIX -${FK_VERSION}-s)
		set_target_properties(${target} PROPERTIES MINSIZEREL_POSTFIX -${FK_VERSION}-min-s)
		set_target_properties(${target} PROPERTIES RELWITHDEBINFO_POSTFIX -${FK_VERSION}-s)
	else()
		set_target_properties(${target} PROPERTIES DEBUG_POSTFIX "_d")
		if(CT_OS_WINDOWS)
			# include the major version number in Windows shared library names (but not import library names)
			set_target_properties(${target} PROPERTIES SUFFIX "_${FK_VERSION}${CMAKE_SHARED_LIBRARY_SUFFIX}")
		endif()
	endif()

	# [WIN32] Set the target folder for Visual Studio
	set_target_properties(${target} PROPERTIES FOLDER "${PROJECT_NAME}")

	# [MACOS] Set Xcode properties
	# if(CT_OS_MACOSX AND BUILD_SHARED_LIBS)
	# endif()

	# Add rule for export symbol
	install(TARGETS ${target} EXPORT ChronotrixConfigExport
			RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT bin
			LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT bin
			ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT dev
			FRAMEWORK DESTINATION "." COMPONENT bin)

	# Add <ct/../../> as public include directory
	target_include_directories(${target}
							PUBLIC "$<BUILD_INTERFACE:${CT_FRWK_DIR}/include>"
							PRIVATE "${CT_FRWK_DIR}/src")
	target_include_directories(${target} INTERFACE $<INSTALL_INTERFACE:include>)

	# Link libraries libs
	if(ARGS_DEPENDS)
		target_link_libraries(${target} PUBLIC ${ARGS_DEPENDS})
	endif()

	# For static builds we need to define the static flag to proper compilation
	if(NOT BUILD_SHARED_LIBS)
		target_compile_definitions(${target} PUBLIC "CT_STATIC")
	endif()

endmacro()

# ----------------------------------------------------------------------------------------------
#
# Add Chronotrix header-only library
#
# @param target {TARGET}			cmake target
# @param HEADERS {STRING[]}		list of header files
# @param DEPENDS? {(TARGET | STRING)[]}	optional - list of dependencies
#
macro(ct_add_header_lib target HEADERS)
	cmake_parse_arguments(ARGS "" "" "DEPENDS" ${ARGN})

	# Create library target
	add_library(${target} INTERFACE)

	# Add rule for export symbol
	install(TARGETS ${target} EXPORT ChronotrixConfigExport
			ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
			LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
			RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
			FRAMEWORK DESTINATION "." COMPONENT bin)

	# Add <ct/../../> as interface include directory
	target_include_directories(${target} INTERFACE
							   $<BUILD_INTERFACE:${CT_FRWK_DIR}/include>
							   $<INSTALL_INTERFACE:include>)

	if(ARGS_DEPENDS)
		target_link_libraries(${target} PUBLIC ${ARGS_DEPENDS})
	endif()
endmacro()

# ----------------------------------------------------------------------------------------------
#
# Add a new executable target
#
# @param target {TARGET}			cmake target
# @param SOURCES {STRING[]}		list of files
# @param DEPENDS? {(TARGET | STRING)[]}	optional - list of dependencies
#
macro(ct_add_executable target)

	# Parse arguments
	cmake_parse_arguments(ARGS "" "" "SOURCES;DEPENDS" ${ARGN})

	# With Win32 with don't have a main file
	# add_executable(${target} WIN32 ${ARGS_SOURCES})
	add_executable(${target} ${ARGS_SOURCES})

	# Set the target folder for Visual Studio
	set_target_properties(${target} PROPERTIES FOLDER "examples")

	# Set the dev suffix
	set_target_properties(${target} PROPERTIES DEBUG_POSTFIX "_d")

	# Set the Visual Studio startup path for debugging
	set_target_properties(${target} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

	# Set target libraries
	target_link_libraries(${target} PRIVATE ctfk_core)
	if(ARGS_DEPENDS)
		target_link_libraries(${target} PRIVATE ${ARGS_DEPENDS})
	endif()

	# [WIN32]
	if(CT_OS_WINDOWS AND BUILD_SHARED_LIBS)
		if(CT_EXAMPLES_POSTCOMMAND STREQUAL "exe_to_bin")
			# Set output folders
			set_target_properties(${target}
						  	  	  PROPERTIES
						 	  	  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
								  )
		elseif(CT_EXAMPLES_POSTCOMMAND STREQUAL "lib_to_exe")
			get_property(VAR TARGET ${target} PROPERTY RUNTIME_OUTPUT_DIRECTORY)
			add_custom_command(TARGET ${target}
							  POST_BUILD        										# Adds a post-build event to MyTest
							  COMMAND ${CMAKE_COMMAND} -E copy_if_different  			# which executes "cmake - E copy_if_different..."
							  "${CMAKE_BINARY_DIR}/bin/chronotrix_core_d.dll"        # <--this is in-file
							  $<TARGET_FILE_DIR:${target}>)                 			# <--this is out-file path
		else()
			message(AUTHOR_WARNING "ct_add_executable: CT_EXAMPLES_POSTCOMMAND is not set correctly.\ The '${target}' target will be placed in ${CMAKE_BINARY_DIR}")
		endif()
	endif()
endmacro()

# ----------------------------------------------------------------------------------------------
#
# Add a new test case
#
# @param target {TARGET}		cmake target
# @param SOURCES {STRING[]}		list of files
# @param DEPENDS? {(TARGET | STRING)[]}	optional - list of dependencies
#
macro(ct_add_test target SOURCES)
	cmake_parse_arguments(ARGS "" "" "DEPENDS" ${ARGN})

	add_executable(${target} ${SOURCES})

	set_target_properties(${target} PROPERTIES FOLDER "tests/unit")
	set_target_properties(${target} PROPERTIES CMAKE_CXX_CLANG_TIDY "")
	set_target_properties(${target} PROPERTIES CXX_CLANG_TIDY "")

	if(ARGS_DEPENDS)
        target_link_libraries(${target} PRIVATE ${ARGS_DEPENDS})
	endif()

	# add catch header as SYSTEM to avoid clang-tidy
	target_include_directories(${target} SYSTEM PRIVATE "${CT_THIRDPARTY_HEADERS}")

	add_test(NAME ctfk_tests COMMAND ${target})

endmacro()


# ----------------------------------------------------------------------------------------------
#
# Create an INTERFACE library target from an external dependecy.
#
# @param target {TARGET}		library target name
# @param INCLUDE? {string[]}	optional - list of includes
# @param LINK? {string[]}		optional - list of libraries to link
#
function(ct_add_external)
    list(GET ARGN 0 target)
    list(REMOVE_AT ARGN 0)

	if (TARGET ${target})
        message(FATAL_ERROR "ct_add_external: Target '${target}' is already defined")
    endif()

	cmake_parse_arguments(ARGS "" "" "INCLUDE;LINK" ${ARGN})
    if (ARGS_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "ct_add_external: Could not parse arguments: ${ARGS_UNPARSED_ARGUMENTS}")
    endif()

	# Create lib
 	add_library(${target} INTERFACE)

	if (ARGS_INCLUDE)
		foreach(include_item IN LISTS ARGS_INCLUDE)
			if (NOT include_item)
				message(FATAL_ERROR "ct_add_external: No path given for include dir ${ARGS_INCLUDE}")
			endif()
			target_include_directories(${target} INTERFACE $<BUILD_INTERFACE:${include_item}>)
		endforeach()
	endif()


	if (ARGS_LINK)
		foreach(lib_item IN LISTS ARGS_LINK)
			if (NOT lib_item)
				message(FATAL_ERROR "ct_add_external: missing item ${ARGS_LINK}")
			endif()
			target_link_libraries(${target} INTERFACE $<BUILD_INTERFACE:${lib_item}>)
		endforeach()
	endif()


	install(TARGETS ${target} EXPORT ChronotrixConfigExport)
endfunction()

# ----------------------------------------------------------------------------------------------
#
# Find package and create INTERFACE library
#
# @param target {TARGET}		library target name
# @param INCLUDE? {string[]}	optional - list of includes
# @param LINK? {string[]}		optional - list of libraries to link
#
function(ct_find_and_create_interface)
	list(GET ARGN 0 target)
    list(REMOVE_AT ARGN 0)

	if (TARGET ${target})
        message(FATAL_ERROR "ct_find_and_create_interface: Target '${target}' is already defined")
    endif()

	cmake_parse_arguments(ARGS "" "" "INCLUDE;LINK" ${ARGN})
    if (ARGS_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "ct_find_and_create_interface: Could not parse arguments: ${ARGS_UNPARSED_ARGUMENTS}")
    endif()


	# if (OS_IOS)
    #     find_host_package(${target} REQUIRED)
    # else()
	find_package(${target} REQUIRED)
    # endif()

	set(include_list "")
	if (ARGS_INCLUDE)
		foreach(include_item IN LISTS ARGS_INCLUDE)
			list(APPEND include_list "${${include_item}}")
		endforeach()
    endif()

	set(link_list "")
	if (ARGS_LINK)
		foreach(lib_item IN LISTS ARGS_LINK)
			SET(current "${${lib_item}}")
			if (NOT current)
				message(FATAL_ERROR "ct_find_and_create_interface: Library not found: ${lib_item}")
			endif()
			list(APPEND link_list ${current})
		endforeach()
    endif()

	ct_add_external(${target} INCLUDE ${include_list} LINK ${link_list})
endfunction()


# ----------------------------------------------------------------------------------------------
#
# Export targets
#
function(ct_export_targets)
	set(CURRENT_DIR "${PROJECT_SOURCE_DIR}/cmake")

	include(CMakePackageConfigHelpers)
	set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

	# Create Version file for the project
	write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/ChronotrixVersionConfig.cmake"
                                     VERSION ${${PROJECT_NAME}_VERSION}
									 COMPATIBILITY SameMajorVersion)

	# Set target build config
	if (BUILD_SHARED_LIBS)
        set(BUILD_CONFIG_NAME "Shared")
    else()
        set(BUILD_CONFIG_NAME "Static")
	endif()
	set(TARGET_CONFIG_FILENAME "Chronotrix${BUILD_CONFIG_NAME}Targets.cmake")

	# Create Targets - (export symbols config)
	export(EXPORT
		ChronotrixConfigExport
		FILE "${CMAKE_CURRENT_BINARY_DIR}/${TARGET_CONFIG_FILENAME}")

	set(CONFIG_PACKAGE_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/chronotrix)
	# configure_package_config_file("${CURRENT_DIR}/ChronotrixConfig.cmake.in"
	# ${CMAKE_CURRENT_BINARY_DIR}/ChronotrixConfig.cmake"
    #    						  INSTALL_DESTINATION "${CONFIG_PACKAGE_DIR}")

	# Add installation rule for targets
	install(EXPORT ChronotrixConfigExport
		   FILE ${TARGET_CONFIG_FILENAME}
		   DESTINATION ${CONFIG_PACKAGE_DIR})

	# Add installation rules
	# TODO: "${CMAKE_CURRENT_BINARY_DIR}/ChronotrixConfig.cmake"
	install(FILES "${CMAKE_CURRENT_BINARY_DIR}/ChronotrixVersionConfig.cmake"
            DESTINATION ${CONFIG_PACKAGE_DIR}
            COMPONENT development)

endfunction()
