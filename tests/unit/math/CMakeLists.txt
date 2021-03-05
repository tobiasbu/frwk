
file(GLOB_RECURSE SRC ${UNIT_DIR}/math/*.cpp)
set(SRC ${SRC})

ct_group(${SRC} TREE ${CMAKE_CURRENT_SOURCE_DIR} NAME "test")

ct_add_test(tests_math_vec2 "${SRC}"
			DEPENDS ctfk_math ctfk_core
)
