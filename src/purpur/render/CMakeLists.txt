
set(INCPATH "${PURPUR_INC}/render")
set(SRCPATH "${PURPUR_SRC}/render")



set(RENDER_INC
	${INCPATH}/export.hpp
	${INCPATH}/context_config.hpp
	${INCPATH}/render_window.hpp
)

set(RENDER_SRC
	${SRCPATH}/render_window.cpp
)

set(RENDER_SUB_INC
	${INCPATH}/opengl/gl_context.hpp
)

set(RENDER_SUB_SRC
	${SRCPATH}/opengl/gl_context.cpp
)

if(PPR_OS_WINDOWS)
	set(RENDER_SUB_INC
		${RENDER_SUB_INC}
		${INCPATH}/opengl/wgl_context.hpp
	)

	set(RENDER_SUB_SRC
		${RENDER_SUB_SRC}
		${SRCPATH}/opengl/wgl_context.cpp
	)

endif()

# root folder
ppr_group(${RENDER_INC})
ppr_group(${RENDER_SRC} IS_IMPL)

# sub-folders
ppr_group(${RENDER_SUB_INC} TREE ${INCPATH})
ppr_group(${RENDER_SUB_SRC} TREE ${SRCPATH} IS_IMPL)

ppr_add_library(purpurina_render
				SOURCES ${RENDER_INC} ${RENDER_SRC} ${RENDER_SUB_INC} ${RENDER_SUB_SRC}
				DEPENDS purpurina_platform
)

find_package(OpenGL)
target_link_libraries(purpurina_render PRIVATE ${OPENGL_gl_LIBRARY})
