
set(INCPATH "${PURPURINA_INC}/platform")
set(SRCPATH "${PURPURINA_SRC}/platform")

set(PLATFORM_INC
	${INCPATH}/export.hpp
	${INCPATH}/window_style.hpp
	${INCPATH}/window.hpp
	${INCPATH}/platform_window.hpp
)

set(PLATFORM_SRC
	"${SRCPATH}/window.cpp"
)

if(PURPURINA_OS_MACOSX)
	set(INC_OS_PATH "${INCPATH}/osx")
	set(SRC_OS_PATH "${SRCPATH}/osx")
	set(LINK_LIBS "-framework Foundation" "-framework AppKit" "-framework IOKit" "-framework Carbon")

	set(PLATFORM_INC
		${PLATFORM_INC}
		${INC_OS_PATH}/cocoa_window.hpp
		${INC_OS_PATH}/cocoa_window_controller.h
		${INC_OS_PATH}/ppr_window.h
		${INC_OS_PATH}/ppr_window_delegate.h
		${INC_OS_PATH}/ppr_application.h
		${INC_OS_PATH}/ppr_application_delegate.h
		${INC_OS_PATH}/autorelease_pool.h

	)

	set(PLATFORM_SRC
		${PLATFORM_SRC}
		${SRC_OS_PATH}/cocoa_window.mm
		${SRC_OS_PATH}/ppr_window.mm
		${SRC_OS_PATH}/ppr_window_delegate.mm
		${SRC_OS_PATH}/ppr_application.mm
		${SRC_OS_PATH}/ppr_application_delegate.mm
		${SRC_OS_PATH}/autorelease_pool.mm
	)

endif()

source_group(TREE ${INCPATH} FILES ${PLATFORM_INC} PREFIX "Header Files")
source_group(TREE ${SRCPATH} FILES ${PLATFORM_SRC} PREFIX "Source Files")


ppr_add_library(purpurina_platform
				SOURCES ${PLATFORM_INC} ${PLATFORM_SRC}
				DEPENDS ${LINK_LIBS}
)

if ((NOT BUILD_SHARED_LIBS) AND PURPURINA_OS_MACOSX)
    target_link_libraries(purpurina_platform PRIVATE -ObjC)
endif()
