
####################################
# PLATFORM
####################################

set(LINK_LIBS "")

# includes
ppr_file_list(ROOT ${INCPATH} OUTPUT INC
	export.hpp
	platform.hpp
	window.hpp
	window_impl.hpp
	window_style.hpp
	window_handle.hpp
	window_properties.hpp
)
ppr_group(${INC})

# sources
ppr_file_list(ROOT ${SRCPATH} OUTPUT SRC
	window.cpp
	window_style.cpp
	window_properties.cpp
)
ppr_group(${SRC} IS_IMPL)


####################################
# OS SPECIFIC FILES
####################################
if(PPR_OS_WINDOWS)
	set(INC_OS_PATH "${INCPATH}/win32")
	set(SRC_OS_PATH "${SRCPATH}/win32")

	# platfrom inc
	ppr_file_list(ROOT ${INC_OS_PATH} OUTPUT PLATFORM_INC
		win32_detail.hpp
		win32_window.hpp
	)

	# platform src
	ppr_file_list(ROOT ${SRC_OS_PATH} OUTPUT PLATFORM_SRC
		platform.cpp
		win32_window.cpp
		#
		win32_messaging.hpp
		win32_messaging.cpp
	)

elseif(PPR_OS_MACOSX)
	set(INC_OS_PATH "${INCPATH}/osx")
	set(SRC_OS_PATH "${SRCPATH}/osx")
	set(LINK_LIBS "-framework Foundation" "-framework AppKit" "-framework IOKit" "-framework Carbon")

	# platfrom inc
	ppr_file_list(ROOT ${INC_OS_PATH} OUTPUT PLATFORM_INC
		cocoa_window.hpp
		cocoa_window_controller.h
		ppr_window.h
		ppr_window_delegate.h
		ppr_application.h
		ppr_application_delegate.h
		autorelease_pool.h
	)

	# platform src
	ppr_file_list(ROOT ${SRC_OS_PATH} OUTPUT PLATFORM_SRC
		platform.mm
		cocoa_window.mm
		ppr_window.mm
		ppr_window_delegate.mm
		ppr_application.mm
		ppr_application_delegate.mm
		autorelease_pool.mm
	)

endif()

# platform groups
ppr_group(${PLATFORM_INC} TREE ${INCPATH})
ppr_group(${PLATFORM_SRC} TREE ${SRCPATH} IS_IMPL)


# make library target
ppr_add_library(purpurina_platform
				SOURCES ${INC} ${SRC} ${PLATFORM_INC} ${PLATFORM_SRC}
				DEPENDS purpurina_core ${LINK_LIBS}
)

# specifc config
if (PPR_OS_MACOSX AND (NOT BUILD_SHARED_LIBS))
    target_link_libraries(purpurina_platform PRIVATE -ObjC)
endif()
