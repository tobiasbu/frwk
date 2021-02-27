
if ((NOT ${CMAKE_VERSION} VERSION_LESS 3.11) AND (NOT OpenGL_GL_PREFERENCE))
    set(OpenGL_GL_PREFERENCE "LEGACY")
endif()
find_package(OpenGL REQUIRED)

if(NOT OPENGL_FOUND)
	message("OpenGL not found (gl.h)")
endif()

if(NOT OPENGL_GLU_FOUND)
    message("OpenGL Utilities not found (glu.h)")
endif()

# sources
set(GLAD_SRC ${CT_EXTLIBS_PATH}/glad/src/glad.c)
set(GLAD_INCLUDE_DIR
	${CT_EXTLIBS_PATH}/glad/include/KHR/khrplatform.h
	${CT_EXTLIBS_PATH}/glad/include/glad/glad.h
)

# target
add_library(glad STATIC ${GLAD_SRC} ${GLAD_INCLUDE_DIR})
target_link_libraries(glad PRIVATE ${OPENGL_LIBRARIES})
target_include_directories(glad PUBLIC "$<BUILD_INTERFACE:${CT_EXTLIBS_PATH}/glad/include>")

set_target_properties(${target} PROPERTIES FOLDER "thirdparty")
