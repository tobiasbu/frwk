
set(SRCPATH "${PROJECT_SOURCE_DIR}/examples")


set(SANDBOX_SRC
	"${SRCPATH}/main.cpp"
)

source_group("Source Files/" FILES ${SANDBOX_SRC})

# Create sandbox executable
ppr_add_executable(sandbox
				   SOURCES ${SANDBOX_SRC}
				   DEPENDS purpurina_platform ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY})
