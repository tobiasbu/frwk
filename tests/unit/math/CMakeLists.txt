
set(INCPATH  ${CMAKE_CURRENT_SOURCE_DIR})

ct_file_list(ROOT ${INCPATH} OUTPUT SRC
	vec2.test.hpp
	vec3.test.hpp
	vec4.test.hpp
	mat3.test.hpp
	mat4.test.hpp
	rect.test.hpp
	main.cpp
)

SET(SRC ${SRC}
	${TESTS_DIR}/commons/math_commons.hpp
)

ct_add_test(tests_math "${SRC}"
			DEPENDS ctfk_math ctfk_core
)
