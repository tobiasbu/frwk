
function(export_targets)

	#set(CURRENT_DIR "${PROJECT_SOURCE_DIR}/cmake")

	include(CMakePackageConfigHelpers)

	# Create Version file for the project
	write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/purpurina-version-config.cmake"
                                     VERSION ${purpurina_VERSION}
                                     COMPATIBILITY SameMajorVersion)

	# configure_package_config_file()

	set(CONFIG_PACKAGE_PATH ${CMAKE_INSTALL_LIBDIR}/cmake/purpurina)

	# Add installation rule which add purpurina-version configuration
	install(FILES "${CMAKE_CURRENT_BINARY_DIR}/purpurina-version-config.cmake"
            DESTINATION ${CONFIG_PACKAGE_PATH}
            COMPONENT development)

endfunction()
