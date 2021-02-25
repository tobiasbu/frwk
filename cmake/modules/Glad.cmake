
include(FindOpenGL)

# Required packages
# find_package(OpenGL REQUIRED COMPONENTS OpenGL)
if(NOT OPENGL_FOUND)
	message("ERROR: OpenGL not found (gl.h)")
endif()

if(NOT OPENGL_GLU_FOUND)
    message("ERROR: OpenGL Utilities not found (glu.h)")
endif()

set(GLAD "${CT_EXTLIBS_DIR}/glad/include")
