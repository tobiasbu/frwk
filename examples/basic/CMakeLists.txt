
# OpenGL
if ((NOT ${CMAKE_VERSION} VERSION_LESS 3.11) AND (NOT OpenGL_GL_PREFERENCE))
    set(OpenGL_GL_PREFERENCE "LEGACY")
endif()
find_package(OpenGL REQUIRED)

# Glad
set(GLAD_SRC ${CT_EXTLIBS_PATH}/glad/src/glad.c)
set(GLAD_INCLUDE_DIR
	${CT_EXTLIBS_PATH}/glad/include/KHR/khrplatform.h
	${CT_EXTLIBS_PATH}/glad/include/glad/glad.h
)

add_library(glad STATIC ${GLAD_SRC} ${GLAD_INCLUDE_DIR})
target_link_libraries(glad PRIVATE ${OPENGL_LIBRARIES})
target_include_directories(glad PUBLIC "$<BUILD_INTERFACE:${CT_EXTLIBS_PATH}/glad/include>")
# target_include_directories(glad PUBLIC ${GLAD_INCLUDE_DIR} )

# Examples

set(SRCPATH "${PROJECT_SOURCE_DIR}/examples/basic")
set(SRC "${SRCPATH}/simple_window/main.cpp")
ct_add_executable(simple_window
				   SOURCES ${SRC}
				   DEPENDS chronotrix_platform)



set(SRC "${SRCPATH}/hello_triangle/main.cpp")
ct_add_executable(hello_triangle
				   SOURCES ${SRC}
				   DEPENDS chronotrix_render glad)

# SET_SOURCE_FILES_PROPERTIES(${GLAD_SRC} PROPERTIES LANGUAGE CXX )
# target_include_directories(hello_triangle PUBLIC ${OPENGL_INCLUDE_DIR} ${GLAD_INCLUDE_DIR})
# target_link_libraries(hello_triangle PRIVATE ${OPENGL_LIBRARIES})
