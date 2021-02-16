
####################################
# RENDER
####################################

# includes
ppr_file_list(ROOT ${INCPATH} OUTPUT INC
	export.hpp
	context_config.hpp
	render_window.hpp
)
ppr_group(${INC})

# sources
ppr_file_list(ROOT ${SRCPATH} OUTPUT SRC
	render_window.cpp
)
ppr_group(${SRC} IS_IMPL)

# includes subfolder
ppr_file_list(ROOT ${INCPATH} OUTPUT SUB_INC
	opengl/gl_context.hpp
)
ppr_group(${SUB_INC} TREE ${INCPATH})

# sources subfolder
ppr_file_list(ROOT ${SRCPATH} OUTPUT SUB_SRC
	opengl/gl_context.cpp
)
ppr_group(${SUB_SRC} TREE ${SRCPATH} IS_IMPL)


####################################
# OS SPECIFIC FILES
####################################
if(PPR_OS_WINDOWS)
	# platfrom inc
	ppr_file_list(ROOT ${INCPATH} OUTPUT SUB_INC CONCAT
		opengl/wgl_context.hpp
	)

	# platfrom src
	ppr_file_list(ROOT ${SRCPATH} OUTPUT SUB_SRC CONCAT
		opengl/wgl_context.cpp
	)
endif()



ppr_add_library(purpurina_render
				SOURCES ${INC} ${SRC} ${SUB_INC} ${SUB_SRC}
				DEPENDS purpurina_platform
)

find_package(OpenGL)
target_link_libraries(purpurina_render PRIVATE ${OPENGL_gl_LIBRARY})
