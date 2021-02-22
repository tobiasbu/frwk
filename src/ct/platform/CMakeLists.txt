
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
)
ct_group(${INC})

# sources
ct_file_list(ROOT ${SRCPATH} OUTPUT SRC
	window.cpp
	window_style.cpp
	window_properties.cpp
	window_impl.hpp
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
	ct_group(${PLATFORM_INC} NAME "win32/include")

	# platform src
	ct_file_list(ROOT ${SRC_OS_PATH} OUTPUT PLATFORM_SRC
		win32_platform.cpp
		win32_window.cpp
		win32_messaging.cpp
	)
	ct_group(${PLATFORM_SRC} NAME "win32/src")

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
		autorelease_pool.h
	)
	ct_group(${PLATFORM_INC} NAME "osx/include")

	# platform src
	ct_file_list(ROOT ${SRC_OS_PATH} OUTPUT PLATFORM_SRC
		cocoa_platform.mm
		cocoa_window.mm
		ct_window.mm
		ct_window_delegate.mm
		ct_application.mm
		ct_application_delegate.mm
		autorelease_pool.mm
	)
	ct_group(${PLATFORM_SRC} NAME "osx/src")

endif()


# make library target
ct_add_library(chronotrix_platform
				SOURCES ${INC} ${SRC} ${PLATFORM_INC} ${PLATFORM_SRC}
				DEPENDS chronotrix_core ${LINK_LIBS}
)

# specifc config
if (CT_OS_MACOSX AND (NOT BUILD_SHARED_LIBS))
    target_link_libraries(chronotrix_platform PRIVATE -ObjC)
endif()
