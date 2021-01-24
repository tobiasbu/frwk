
set(INCPATH "${PURPURINA_INC}/core")
set(SRCPATH "${PURPURINA_SRC}/core")

# Root folder
set(CORE_INC_CONFIG
	"${INCPATH}/config.hpp"
	"${INCPATH}/export.hpp"
	"${PURPURINA_INC}/purpur.hpp"
)

# Sub-folders
set(CORE_INC
	"${INCPATH}/macros/helper_macros.hpp"
	"${INCPATH}/error/exception.hpp"
	"${INCPATH}/debug/assert/assert.hpp"
	"${INCPATH}/debug/assert/assert_handler.hpp"
	"${INCPATH}/debug/assert/assertion_exception.hpp"
	"${INCPATH}/debug/break.hpp"
)


set(CORE_SRC
	"${SRCPATH}/error/exception.cpp"
	"${SRCPATH}/debug/logger.cpp"
	"${SRCPATH}/debug/assert/assert_handler.cpp"
	"${SRCPATH}/debug/assert/assertion_exception.cpp"
)

source_group("Header Files/" FILES ${CORE_INC_CONFIG})

source_group(TREE ${INCPATH} FILES ${CORE_INC} PREFIX "Header Files")
source_group(TREE ${SRCPATH} FILES ${CORE_SRC} PREFIX "Source Files")

ppr_add_library(purpurina_core SOURCES ${CORE_INC_CONFIG} ${CORE_INC} ${CORE_SRC})
