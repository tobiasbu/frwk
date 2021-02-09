
set(INCPATH "${PURPUR_INC}/platform")
set(SRCPATH "${PURPUR_SRC}/platform")
set(LINK_LIBS "")

set(PLATFORM_INC
	${INCPATH}/export.hpp
	${INCPATH}/platform.hpp
	${INCPATH}/window.hpp
	${INCPATH}/window_impl.hpp
	${INCPATH}/window_style.hpp
	${INCPATH}/window_handle.hpp
	${INCPATH}/window_properties.hpp
)

set(PLATFORM_SRC
	${SRCPATH}/window.cpp
	${SRCPATH}/window_style.cpp
	${SRCPATH}/window_properties.cpp
)

if(PPR_OS_WINDOWS)
	set(INC_OS_PATH "${INCPATH}/win32")
	set(SRC_OS_PATH "${SRCPATH}/win32")

	set(PLATFORM_SUB_INC
		${INC_OS_PATH}/win32_detail.hpp
		${INC_OS_PATH}/win32_window.hpp
	)

	set(PLATFORM_SUB_SRC
		${SRC_OS_PATH}/platform.cpp
		${SRC_OS_PATH}/win32_window.cpp
	)

	# internal

	set(PLATFORM_SUB_SRC
		${PLATFORM_SUB_SRC}
		${SRC_OS_PATH}/win32_messaging.hpp
		${SRC_OS_PATH}/win32_messaging.cpp
	)


elseif(PPR_OS_MACOSX)

	set(INC_OS_PATH "${INCPATH}/osx")
	set(SRC_OS_PATH "${SRCPATH}/osx")
	set(LINK_LIBS "-framework Foundation" "-framework AppKit" "-framework IOKit" "-framework Carbon")

	set(PLATFORM_SUB_INC
		${INC_OS_PATH}/cocoa_window.hpp
		${INC_OS_PATH}/cocoa_window_controller.h
		${INC_OS_PATH}/ppr_window.h
		${INC_OS_PATH}/ppr_window_delegate.h
		${INC_OS_PATH}/ppr_application.h
		${INC_OS_PATH}/ppr_application_delegate.h
		${INC_OS_PATH}/autorelease_pool.h

	)

	set(PLATFORM_SUB_SRC
		${SRC_OS_PATH}/platform.mm
		${SRC_OS_PATH}/cocoa_window.mm
		${SRC_OS_PATH}/ppr_window.mm
		${SRC_OS_PATH}/ppr_window_delegate.mm
		${SRC_OS_PATH}/ppr_application.mm
		${SRC_OS_PATH}/ppr_application_delegate.mm
		${SRC_OS_PATH}/autorelease_pool.mm
	)

endif()


# root folder
source_group("Header Files/" FILES ${PLATFORM_INC})
source_group("Source Files/" FILES ${PLATFORM_SRC})


# sub-folders
source_group(TREE ${INCPATH} FILES ${PLATFORM_SUB_INC} PREFIX "Header Files")
source_group(TREE ${SRCPATH} FILES ${PLATFORM_SUB_SRC} PREFIX "Source Files")


ppr_add_library(purpurina_platform
				SOURCES ${PLATFORM_INC} ${PLATFORM_SRC} ${PLATFORM_SUB_INC} ${PLATFORM_SUB_SRC}
				DEPENDS ${LINK_LIBS}
)

if (PPR_OS_MACOSX AND (NOT BUILD_SHARED_LIBS))
    target_link_libraries(purpurina_platform PRIVATE -ObjC)
endif()
