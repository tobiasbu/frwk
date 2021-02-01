
# include(CTest)
# Include(FetchContent)


# Catch2 config
set(CATCH_INSTALL_HELPERS OFF)
set(BUILD_TESTING OFF)
set(CATCH_BUILD_TESTING OFF)
set(CATCH_INSTALL_DOCS OFF)

# catch main file
set(CATCH_MAIN ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)


file(GLOB CORE_TEST_SRC CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/core/*.cpp)

set(TEST_SRC
	${CATCH_MAIN}
	${CORE_TEST_SRC}
)

ppr_add_test(purpurina_core_tests
			"${TEST_SRC}"
			 purpurina_core
)
