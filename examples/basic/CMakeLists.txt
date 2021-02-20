
set(SRCPATH "${PROJECT_SOURCE_DIR}/examples/basic")

set(SRC "${SRCPATH}/simple_window/main.cpp")
ct_add_executable(simple_window
				   SOURCES ${SRC}
				   DEPENDS chronotrix_platform)
