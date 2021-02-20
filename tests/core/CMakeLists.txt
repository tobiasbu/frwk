

file(GLOB_RECURSE CORE_TEST_SRC
	 ${CMAKE_CURRENT_SOURCE_DIR}/utils/*.cpp)

set(TEST_SRC
	${CATCH_MAIN}
	${CORE_TEST_SRC}
)

ct_group(${CATCH_MAIN} TREE ${TESTS_PATH} NAME "_")
ct_group(${CORE_TEST_SRC} TREE ${CMAKE_CURRENT_SOURCE_DIR}/utils NAME "utils")

ct_add_test(chronotrix_core_tests
			"${TEST_SRC}"
			chronotrix_core
)
