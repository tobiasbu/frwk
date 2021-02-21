
####################################
# RENDER
####################################

# includes
ct_file_list(ROOT ${INCPATH} OUTPUT INC
	export.hpp
	context_config.hpp
	render_window.hpp
	render_context.hpp
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

####################################
# OS SPECIFIC FILES
####################################
if(CT_OS_WINDOWS)

	# platfrom src
	ct_file_list(ROOT ${SRCPATH} OUTPUT SUB_SRC CONCAT
		opengl/wgl_context.hpp
		opengl/wgl_context.cpp
		opengl/win32_internal.hpp
		opengl/win32_internal.cpp
		opengl/win32_render.cpp
	)
endif()

ct_add_library(chronotrix_render
				SOURCES ${INC} ${SRC} ${SUB_SRC}
				DEPENDS chronotrix_platform
)

find_package(OpenGL)
target_link_libraries(chronotrix_render PRIVATE ${OPENGL_gl_LIBRARY})
