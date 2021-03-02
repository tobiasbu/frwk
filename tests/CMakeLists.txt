
set(TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(BENCH_DIR ${TESTS_DIR}/benchmark)
set(UNIT_DIR ${TESTS_DIR}/unit)

add_subdirectory(benchmark)

add_subdirectory(unit)
