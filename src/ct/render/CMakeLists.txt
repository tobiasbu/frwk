
####################################
# RENDER
####################################

# includes
ct_file_list(ROOT ${INCPATH} OUTPUT INC
	export.hpp
	context_config.hpp
	render_window.hpp
)
ct_group(${INC})

# sources
ct_file_list(ROOT ${SRCPATH} OUTPUT SRC
	render_window.cpp
)
ct_group(${SRC} IS_IMPL)

# includes subfolder
ct_file_list(ROOT ${INCPATH} OUTPUT SUB_INC
	opengl/gl_context.hpp
)
ct_group(${SUB_INC} TREE ${INCPATH})

# sources subfolder
ct_file_list(ROOT ${SRCPATH} OUTPUT SUB_SRC
	opengl/gl_context.cpp
)
ct_group(${SUB_SRC} TREE ${SRCPATH} IS_IMPL)


####################################
# OS SPECIFIC FILES
####################################
if(CT_OS_WINDOWS)
	# platfrom inc
	ct_file_list(ROOT ${INCPATH} OUTPUT SUB_INC CONCAT
		opengl/wgl_context.hpp
	)

	# platfrom src
	ct_file_list(ROOT ${SRCPATH} OUTPUT SUB_SRC CONCAT
		opengl/wgl_context.cpp
	)
endif()



ct_add_library(chronotrix_render
				SOURCES ${INC} ${SRC} ${SUB_INC} ${SUB_SRC}
				DEPENDS chronotrix_platform
)

find_package(OpenGL)
target_link_libraries(chronotrix_render PRIVATE ${OPENGL_gl_LIBRARY})
