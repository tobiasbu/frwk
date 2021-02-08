

file(GLOB_RECURSE CORE_TEST_SRC
	 ${CMAKE_CURRENT_SOURCE_DIR}/utils/*.cpp)

set(TEST_SRC
	${CATCH_MAIN}
	${CORE_TEST_SRC}
)

ppr_add_test(purpurina_core_tests
			"${TEST_SRC}"
			 purpurina_core
)
