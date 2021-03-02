
include(${CT_THIRDPARTY_DIR}/nanobench.cmake)

function(add_bench target SOURCES)
	cmake_parse_arguments(ARGS "" "" "DEPENDS" ${ARGN})

	add_executable(${target} ${SOURCES})
	set_target_properties(${target} PROPERTIES FOLDER "bench")
	set_target_properties(${target} PROPERTIES CMAKE_CXX_CLANG_TIDY "")

	if(ARGS_DEPENDS)
        target_link_libraries(${target} PRIVATE ${ARGS_DEPENDS} nanobench)
	else()
		target_link_libraries(${target} PRIVATE nanobench)
	endif()

	target_include_directories(${target} SYSTEM PRIVATE "${CT_THIRDPARTY_HEADERS}")

	add_test(NAME chronotrix_tests COMMAND ${target})

endfunction()

set(SRC ${BENCH_DIR}/virtual_alternatives.cpp)
ct_group(${SRC} TREE ${TESTS_DIR} NAME "benchmark")

add_bench(bench_virtual_alter "${SRC}" DEPENDS chronotrix_core)
