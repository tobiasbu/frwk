
set(SRCPATH "${PROJECT_SOURCE_DIR}/examples")


set(EXAMPLE_SRC "${SRCPATH}/simple_window/main.cpp")
ppr_add_executable(simple_window
				   SOURCES ${EXAMPLE_SRC}
				   DEPENDS purpurina_platform)



set(EXAMPLE_SRC "${SRCPATH}/hello_triangle/main.cpp")
ppr_add_executable(hello_triangle
				   SOURCES ${EXAMPLE_SRC}
				   DEPENDS purpurina_render)
