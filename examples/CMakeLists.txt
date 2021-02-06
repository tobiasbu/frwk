
set(SRCPATH "${PROJECT_SOURCE_DIR}/examples")


set(SANDBOX_SRC
	"${SRCPATH}/main.cpp"
)

source_group("Source Files/" FILES ${SANDBOX_SRC})

set(DEPENDENCIES
	purpurina_render
	${OPENGL_gl_LIBRARY}
	${OPENGL_glu_LIBRARY}
)

# Create sandbox executable
ppr_add_executable(sandbox
				   SOURCES ${SANDBOX_SRC}
				   DEPENDS ${DEPENDENCIES})
