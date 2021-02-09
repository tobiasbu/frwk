
set(SRCPATH "${PROJECT_SOURCE_DIR}/examples")


set(EXAMPLE_SRC
	"${SRCPATH}/window/main.cpp"
)

source_group("Source Files/" FILES ${EXAMPLE_SRC})

set(DEPENDENCIES
	purpurina_render
	# ${OPENGL_gl_LIBRARY}
	# ${OPENGL_glu_LIBRARY}
)

# Create sandbox executable
ppr_add_executable(window
				   SOURCES ${EXAMPLE_SRC}
				   DEPENDS ${DEPENDENCIES})
