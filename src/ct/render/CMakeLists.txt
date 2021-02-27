
####################################
# RENDER
####################################

# includes
ct_file_list(ROOT ${INCPATH} OUTPUT INC
	export.hpp
	render_types.hpp
	render_window.hpp
	render_context.hpp
	context_config.hpp
)
ct_group(${INC})

# sources
ct_file_list(ROOT ${SRCPATH} OUTPUT SRC
	render_window.cpp
	render_context.cpp
	context_impl.hpp
	context_impl.cpp
)
ct_group(${SRC} IS_IMPL)

set(SRC_GL_PATH "${SRCPATH}/opengl")

####################################
# OS SPECIFIC FILES
####################################
if(CT_OS_WINDOWS)


	ct_file_list(ROOT ${SRCPATH} OUTPUT SUB_SRC CONCAT
		win32/win32_internal.hpp
		win32/win32_internal.cpp
		win32/win32_render.cpp
	)

	set(SUB_SRC
		${SUB_SRC}
		${SRC_GL_PATH}/wgl_context.hpp
		${SRC_GL_PATH}/wgl_context.cpp
	)

elseif(CT_OS_MACOSX)

	set(LINK_LIBS "-framework Foundation" "-framework AppKit")

	ct_file_list(ROOT ${SRCPATH} OUTPUT SUB_SRC CONCAT
		cocoa_render.cpp
	)

	set(SUB_SRC
		${SUB_SRC}
		${SRC_GL_PATH}/nsgl_context.hpp
		${SRC_GL_PATH}/nsgl_context.mm
		${SRC_GL_PATH}/ct_opengl_view.h
		${SRC_GL_PATH}/ct_opengl_view.mm
	)

endif()

ct_add_library(chronotrix_render
				SOURCES ${INC} ${SRC} ${SUB_SRC}
				DEPENDS chronotrix_platform ${LINK_LIBS}
)

find_package(OpenGL)
target_link_libraries(chronotrix_render PRIVATE ${OPENGL_gl_LIBRARY})
