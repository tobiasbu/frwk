
set(INCPATH "${PURPURINA_INC}/platform")
set(SRCPATH "${PURPURINA_SRC}/platform")


# Sub-folders
set(PLATFORM_INC
	"${INCPATH}/window.hpp"
	"${INCPATH}/platform_window.hpp"
)

if(PURPURINA_OS_MACOSX)
	set(INC_OS_PATH "${INCPATH}/osx")
	set(PLATFORM_INC
		"${PLATFORM_INC}"
		"${INC_OS_PATH}/cocoa_window.hpp"
	)
endif()

# set(PLATFORM_SRC
# 	"${SRCPATH}/error/exception.cpp"
# 	"${SRCPATH}/debug/logger.cpp"
# 	"${SRCPATH}/debug/assert/assert_handler.cpp"
# 	"${SRCPATH}/debug/assert/assertion_exception.cpp"
# )


source_group(TREE ${INCPATH} FILES ${PLATFORM_INC} PREFIX "Header Files")
# source_group(TREE ${SRCPATH} FILES ${CORE_SRC} PREFIX "Source Files")


ppr_add_library(purpurina-platform
			    SOURCES ${PLATFORM_INC}
)
