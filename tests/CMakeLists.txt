
# include(CTest)
# Include(FetchContent)


# Catch2 config
set(CATCH_INSTALL_HELPERS OFF)
set(BUILD_TESTING OFF)
set(CATCH_BUILD_TESTING OFF)
set(CATCH_INSTALL_DOCS OFF)

# catch main file
set(TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CATCH_MAIN ${TESTS_DIR}/main.cpp)


add_subdirectory(core)
add_subdirectory(misc)
