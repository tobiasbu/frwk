
set(INCPATH "${PURPURINA_PACKAGES_DIR}/sandbox/include/purpurina/sandbox")
set(SRCPATH "${PURPURINA_PACKAGES_DIR}/sandbox/src/purpurina/sandbox")


set(SANDBOX_SRC
	"${SRCPATH}/main.cpp"
)

ppr_make_source_groups(SOURCES ${SANDBOX_SRC})

# Create sandbox executable
ppr_add_executable(sandbox
				   SOURCES ${SANDBOX_SRC}
				   DEPENDS ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY})

# message("${OPENGL_glu_LIBRARY}")
# target_include_directories(sandbox PUBLIC ${OPENGL_INCLUDE_DIR})
# ppr_link(sandbox ${OPENGL_LIBRARIES} ${OPENGL_INCLUDE_DIR})

# target_link_directories(sandbox ${OPENGL_INCLUDE_DIR})

# target_link_libraries(${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY})
# target_link_libraries(sandbox ${OPENGL_LIBRARIES})
