include(CMakeParseArguments)

#
# Create multi option selector
# In CMake GUI this will turn into a combobox
#
# Usage: ppr_multi_options(MY_VARIABLE							# variable name
#						   "default_option"						# default value
#						   "default_option;option_a;option_b"	# available options
#						   "Defines the post build command"		# description
# 						  )
#
function (ppr_multi_options variable default options docstring)
	if(NOT DEFINED ${variable})
		set(${variable} ${default})
	endif()

	set(${variable} ${default} CACHE STRING ${docstring})
	set_property(CACHE ${variable} PROPERTY STRINGS ${options})
endfunction()


#
# Create Purpurina CMake property
#
# Usage: ppr_set_prop(MY_VARIABLE 					# variable name
#					  BOOL							# variable type
# 					  FALSE							# default value
# 					  "Compile Static Library"  	# variable description
# 					  )
#
function(ppr_set_prop variable default type docstring)
	if(NOT DEFINED ${variable})
        set(${variable} ${default})
    endif()
	message(${variable})
    set(${variable} ${default} CACHE ${type} ${docstring} FORCE)
endfunction()

#
# Set Xcode property
#
# Usage: ppr_set_xcode_prop(target 					# target
#					  		xcode_prop				# property name
# 					  		xcode_value				# property value
# 					  		)
#
macro (ppr_set_xcode_prop target xcode_prop xcode_value)
    set_property (TARGET ${TARGET} PROPERTY XCODE_ATTRIBUTE_${xcode_prop} ${xcode_value})
endmacro ()

#
# Add Purpurina library
#
# Usage: ppr_add_library(target
#						 SOURCES # list of files
# )
#
macro(ppr_add_library target)

	# Parse arguments
	cmake_parse_arguments(ARGS "" "" "SOURCES;DEPENDS" ${ARGN})
	if (NOT "${ARGS_UNPARSED_ARGUMENTS}" STREQUAL "" AND NOT ${ARGS_UNPARSED_ARGUMENTS} STREQUAL "LINK")
        message(FATAL_ERROR "Extra unparsed arguments when calling ppr_add_library: ${ARGS_UNPARSED_ARGUMENTS}")
    endif()

	# Create library target
	add_library(${target} ${ARGS_SOURCES})

	# Define Export symbol
	string(REPLACE "-" "_" EXPORT_SYMBOL_NAME "${target}")
	string(TOUPPER "${EXPORT_SYMBOL_NAME}" EXPORT_SYMBOL_NAME)
	set_target_properties(${target} PROPERTIES DEFINE_SYMBOL "${EXPORT_SYMBOL_NAME}_EXPORTS")

	# Set libray output files names
	if(PPR_STATIC)
		set_target_properties(${target} PROPERTIES DEBUG_POSTFIX -${purpurina_VERSION}-s.dev)
		set_target_properties(${target} PROPERTIES RELEASE_POSTFIX -${purpurina_VERSION}-s)
		set_target_properties(${target} PROPERTIES MINSIZEREL_POSTFIX -${purpurina_VERSION}-min-s)
		set_target_properties(${target} PROPERTIES RELWITHDEBINFO_POSTFIX -${purpurina_VERSION}-s)
	else()
		if(PPR_OS_WINDOWS)
			# include the major version number in Windows shared library names (but not import library names)
			set_target_properties(${target} PROPERTIES DEBUG_POSTFIX "-debug")
			set_target_properties(${target} PROPERTIES SUFFIX "${CMAKE_SHARED_LIBRARY_SUFFIX}")
		else()
			set_target_properties(${target} PROPERTIES DEBUG_POSTFIX "-debug")
		endif()
	endif()

	# [WIN32] Set the target folder for Visual Studio
	set_target_properties(${target} PROPERTIES FOLDER "purpurina_frwk")

	# [MACOS] Set Xcode properties
	if(PPR_OS_MACOSX AND BUILD_SHARED_LIBS)

	endif()

	# Add rule for export symbol
	install(TARGETS ${target} EXPORT PurpurinaConfigExport
			RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT bin
			LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT bin
			ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT dev
			FRAMEWORK DESTINATION "." COMPONENT bin)

	# Add <purpur/../../> as public include directory
	# string(REGEX MATCH "^[a-z]*-([a-z]*)$" MATCHED "${target}")
	target_include_directories(${target}
							PUBLIC "$<BUILD_INTERFACE:${PURPUR_FRWK_PATH}/include>"
							PRIVATE "${PURPUR_FRWK_PATH}/src")
	target_include_directories(${target} INTERFACE $<INSTALL_INTERFACE:include>)

	# Link libraries libs
	if(ARGS_DEPENDS)
		target_link_libraries(${target} PRIVATE ${ARGS_DEPENDS})
	endif()

	# For static builds we need to define the static flag to proper compilation
	if(NOT BUILD_SHARED_LIBS)
		target_compile_definitions(${target} PUBLIC "PPR_STATIC")
	endif()

endmacro()

#
# Add a new Sandbox executable target
#
# Usage: ppr_add_executable(example
# 						 SOURCES file.cpp...
#						 DEPENDS purpurina-analytics)
#
macro(ppr_add_executable target)

	# Parse arguments
	cmake_parse_arguments(ARGS "" "" "SOURCES;DEPENDS" ${ARGN})

	# With Win32 with don't have a main file
	# add_executable(${target} WIN32 ${ARGS_SOURCES})
	add_executable(${target} ${ARGS_SOURCES})

	# Set the target folder for Visual Studio
	set_target_properties(${target} PROPERTIES FOLDER "examples")

	# Set the dev suffix
	set_target_properties(${target} PROPERTIES DEBUG_POSTFIX "-debug")

	# Set the Visual Studio startup path for debugging
	set_target_properties(${target} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

	# Set target libraries - Core
	if(ARGS_DEPENDS)
		target_link_libraries(${target} PRIVATE purpurina_core ${ARGS_DEPENDS})
	else()
		target_link_libraries(${target} PRIVATE purpurina_core)
	endif()

	# target_include_directories(${target}
	# PUBLIC "$<BUILD_INTERFACE:${PURPUR_FRWK_PATH}/>")
	# // ${PROJECT_SOURCE_DIR}/${target}/include

	# [WIN32]
	if(PPR_OS_WINDOWS AND BUILD_SHARED_LIBS)
		if(PURPUR_EXAMPLES_POSTCOMMAND STREQUAL "exe_to_bin")
			# Set output folders
			set_target_properties(${target}
						  	  	  PROPERTIES
						 	  	  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
								  )
		elseif(PURPUR_EXAMPLES_POSTCOMMAND STREQUAL "lib_to_exe")
			get_property(VAR TARGET ${target} PROPERTY RUNTIME_OUTPUT_DIRECTORY)
			add_custom_command(TARGET ${target}
							  POST_BUILD        										# Adds a post-build event to MyTest
							  COMMAND ${CMAKE_COMMAND} -E copy_if_different  			# which executes "cmake - E copy_if_different..."
							  "${CMAKE_BINARY_DIR}/bin/purpurina-core-debug.dll"        # <--this is in-file
							  $<TARGET_FILE_DIR:${target}>)                 			# <--this is out-file path
		else()
			message(AUTHOR_WARNING "PURPURINA_SANDOBOX_POSTCOMMAND is not set correctly.\ The '${target}' target will be placed in ${CMAKE_BINARY_DIR}")
		endif()
	endif()
endmacro()

#
# Add a new Sandbox executable target
#
# Usage: ppr_add_test(example
# 					  SOURCES file.cpp...
#					  DEPENDS purpurina-analytics)
#
function(ppr_add_test target SOURCES DEPENDS)

	add_executable(${target} ${SOURCES})

	set_target_properties(${target} PROPERTIES FOLDER "tests")

	if(DEPENDS)
        target_link_libraries(${target} PRIVATE ${DEPENDS})
	endif()

	target_include_directories(${target} PUBLIC "${PURPUR_EXTLIBS_PATH}/headers")

	add_test(NAME purpurina_tests COMMAND ${target})

endfunction()

function(ppr_export_targets)
	set(CURRENT_DIR "${PROJECT_SOURCE_DIR}/cmake")

	include(CMakePackageConfigHelpers)
	set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

	# Create Version file for the project
	write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/PurpurinaVersionConfig.cmake"
                                     VERSION ${purpurina_VERSION}
									 COMPATIBILITY SameMajorVersion)

	# Set target build config
	if (BUILD_SHARED_LIBS)
        set(BUILD_CONFIG_NAME "Shared")
    else()
        set(BUILD_CONFIG_NAME "Static")
	endif()
	set(TARGET_CONFIG_FILENAME "Purpurina${BUILD_CONFIG_NAME}Targets.cmake")

	# Create Targets - (export symbols config)
	export(EXPORT
		PurpurinaConfigExport
		FILE "${CMAKE_CURRENT_BINARY_DIR}/${TARGET_CONFIG_FILENAME}")

	set(CONFIG_PACKAGE_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/purpurina)
	# configure_package_config_file("${CURRENT_DIR}/PurpurinaConfig.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/PurpurinaConfig.cmake"
    #    						  INSTALL_DESTINATION "${CONFIG_PACKAGE_DIR}")

	# Add installation rule for targets
	install(EXPORT PurpurinaConfigExport
		   FILE ${TARGET_CONFIG_FILENAME}
		   DESTINATION ${CONFIG_PACKAGE_DIR})

	# Add installation rules
	# TODO: "${CMAKE_CURRENT_BINARY_DIR}/PurpurinaConfig.cmake"
	install(FILES "${CMAKE_CURRENT_BINARY_DIR}/PurpurinaVersionConfig.cmake"
            DESTINATION ${CONFIG_PACKAGE_DIR}
            COMPONENT development)

endfunction()
