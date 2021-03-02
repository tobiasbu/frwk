
file(GLOB_RECURSE CORE_TEST_SRC
	 ${UNIT_DIR}/core/utils/*.cpp)
set(SRC ${CORE_TEST_SRC})

ct_group(${CORE_TEST_SRC} TREE ${CMAKE_CURRENT_SOURCE_DIR}/utils NAME "utils")

ct_add_test(tests_chronotrix_core "${SRC}"
			DEPENDS chronotrix_core
)
