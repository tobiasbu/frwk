
# Set project cmake modules
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules")

#############################################
####	 OUTPUT AND LIB DIRECTORIES 	 ####
#############################################


# Set output folders for libraries
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")

if (CT_OS_WINDOWS AND CT_EXAMPLES_POSTCOMMAND STREQUAL "exe_to_bin")
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
endif()

# Add modules
# include(Glad)

#############################################
####		ADD CHRONOTRIX PACKAGES		 ####
#############################################

ct_add_lib_directory(core)

ct_add_lib_directory(platform)

ct_add_lib_directory(render)
