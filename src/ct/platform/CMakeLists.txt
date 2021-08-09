
####################################
# PLATFORM
####################################

set(LINK_LIBS "")

# includes
ct_file_list(ROOT ${INCPATH} OUTPUT INC
	export.hpp
	platform.hpp
	window.hpp
	window_style.hpp
	window_handle.hpp
	window_properties.hpp
	render_types.hpp
	render_window.hpp
	render_context.hpp
	context_config.hpp
)
ct_group(${INC})

# sources
ct_file_list(ROOT ${SRCPATH} OUTPUT SRC
	window.cpp
	window_style.cpp
	window_properties.cpp
	window_impl.hpp
	render_window.cpp
	render_context.cpp
	context_impl.hpp
)

ct_group(${SRC} IS_IMPL)

####################################
# OS SPECIFIC FILES
####################################
if(CT_OS_WINDOWS)
	set(INC_OS_PATH "${INCPATH}/win32")
	set(SRC_OS_PATH "${SRCPATH}/win32")

	# platfrom inc
	ct_file_list(ROOT ${SRC_OS_PATH} OUTPUT PLATFORM_INC
		win32_window.hpp
		win32_messaging.hpp
	)
	set(PLATFORM_INC
		${PLATFORM_INC}
		${INCPATH}/detail/win32_detail.hpp
	)
	ct_group(${PLATFORM_INC} NAME "${CT_HEADER_GROUP}/win32")

	# platform src
	ct_file_list(ROOT ${SRC_OS_PATH} OUTPUT PLATFORM_SRC
		win32_platform.cpp
		win32_window.cpp
		win32_messaging.cpp
		win32_render.cpp
		win32_internal.hpp
		win32_internal.cpp
		wgl_context.hpp
		wgl_context.cpp

	)
	ct_group(${PLATFORM_SRC} NAME "${CT_SOURCE_GROUP}/win32")

elseif(CT_OS_MACOSX)
	set(INC_OS_PATH "${INCPATH}/osx")
	set(SRC_OS_PATH "${SRCPATH}/osx")
	set(LINK_LIBS "-framework Foundation" "-framework AppKit" "-framework IOKit" "-framework Carbon")

	# platfrom inc
	ct_file_list(ROOT ${SRC_OS_PATH} OUTPUT PLATFORM_INC
		cocoa_window.hpp
		cocoa_window_controller.h
		ct_window.h
		ct_window_delegate.h
		ct_application.h
		ct_application_delegate.h
		ct_opengl_view.h
		nsgl_context.hpp
		autorelease_pool.h
	)
	ct_group(${PLATFORM_INC} NAME "osx/include")

	# platform src
	ct_file_list(ROOT ${SRC_OS_PATH} OUTPUT PLATFORM_SRC
		cocoa_render.cpp
		cocoa_platform.mm
		cocoa_window.mm
		ct_window.mm
		ct_window_delegate.mm
		ct_application.mm
		ct_application_delegate.mm
		ct_opengl_view.mm
		nsgl_context.mm
		autorelease_pool.mm
	)
	ct_group(${PLATFORM_SRC} NAME "osx/src")

elseif(CT_OS_LINUX)
	set(INC_OS_PATH "${INCPATH}/x11")
	set(SRC_OS_PATH "${SRCPATH}/x11")

	ct_file_list(ROOT ${SRC_OS_PATH} OUTPUT PLATFORM_INC
		x11.hpp
		x11_window.hpp
		glx_context.hpp
		glx_lib.hpp
	)

	# platform src
	ct_file_list(ROOT ${SRC_OS_PATH} OUTPUT PLATFORM_SRC
		x11.cpp
		x11_window.cpp
		x11_platform.cpp
		glx_lib.cpp
		glx_context.cpp
	)

	ct_group(${PLATFORM_INC} NAME "x11/include")
	set(LINK_LIBS ${CMAKE_DL_LIBS})

endif()


# Make library target
ct_add_library(ctfk_platform
				SOURCES ${INC} ${SRC} ${PLATFORM_INC} ${PLATFORM_SRC}
				DEPENDS ctfk_math ctfk_core ${LINK_LIBS}
)

# Add OpenGL
find_package(OpenGL)
target_link_libraries(ctfk_platform PRIVATE ${OPENGL_gl_LIBRARY})

# [MACOSX] specifc config
if (CT_OS_MACOSX AND (NOT BUILD_SHARED_LIBS))
    target_link_libraries(ctfk_platform PRIVATE -ObjC)
endif()

# [LINUX] specifc config
if(CT_OS_LINUX)
	ct_find_and_create_interface(X11
								 INCLUDE "X11_INCLUDE_DIR"
								 LINK "X11_X11_LIB")
    target_link_libraries(ctfk_platform PRIVATE X11)
	# target_link_libraries(ctfk_platform PRIVATE dl)
endif()
