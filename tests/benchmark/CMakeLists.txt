
function(add_bench target SOURCES)
	cmake_parse_arguments(ARGS "" "" "DEPENDS" ${ARGN})

	add_executable(${target} ${SOURCES})
	set_target_properties(${target} PROPERTIES FOLDER "tests/bench")
	set_target_properties(${target} PROPERTIES CMAKE_CXX_CLANG_TIDY "")

	if(ARGS_DEPENDS)
        target_link_libraries(${target} PRIVATE ${ARGS_DEPENDS})
	endif()

	target_include_directories(${target} SYSTEM PRIVATE "${CT_THIRDPARTY_HEADERS}" "${BENCH_DIR}/profiler")

	add_test(NAME "${target}" COMMAND ${target})

endfunction()

set(SRC ${BENCH_DIR}/virtual_alternatives.test.cpp)
add_bench(bench_virtual_alter "${SRC}" DEPENDS ctfk_core)


ct_file_list(ROOT "${BENCH_DIR}/matrix_inverse" OUTPUT SRC
	algorithms.hpp
	mesa_algorithm.hpp
	main.cpp
)

SET(SRC ${SRC}
	${TESTS_DIR}/commons/math_commons.hpp
)
add_bench(bench_mat4_inverse "${SRC}" DEPENDS ctfk_core ctfk_math)
