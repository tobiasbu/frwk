
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
source_group("Header Files/" FILES ${RENDER_INC})
source_group("Source Files/" FILES ${RENDER_SRC})

# sub-folders
source_group(TREE ${INCPATH} FILES ${RENDER_SUB_INC} PREFIX "Header Files")
source_group(TREE ${SRCPATH} FILES ${RENDER_SUB_SRC} PREFIX "Source Files")


ppr_add_library(purpurina_render
				SOURCES ${RENDER_INC} ${RENDER_SRC} ${RENDER_SUB_INC} ${RENDER_SUB_SRC}
				DEPENDS purpurina_platform
)
