

include(${CT_EXTLIBS_PATH}/glad.cmake)

# Examples
set(SRCPATH "${PROJECT_SOURCE_DIR}/examples/basic")
set(SRC "${SRCPATH}/simple_window/main.cpp")
ct_add_executable(simple_window
				   SOURCES ${SRC}
				   DEPENDS chronotrix_platform)



set(SRC "${SRCPATH}/hello_triangle/main.cpp")
ct_add_executable(hello_triangle
				   SOURCES ${SRC}
				   DEPENDS chronotrix_render glad)
