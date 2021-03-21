
set(INCPATH  ${CMAKE_CURRENT_SOURCE_DIR})

ct_file_list(ROOT ${INCPATH} OUTPUT SRC
	rect.test.hpp
	vec2.test.hpp
	vec3.test.hpp
	vec4.test.hpp
	commons.hpp
	main.cpp
)


ct_group(${SRC} TREE ${CMAKE_CURRENT_SOURCE_DIR} NAME "test")

ct_add_test(tests_math "${SRC}"
			DEPENDS ctfk_math ctfk_core
)
