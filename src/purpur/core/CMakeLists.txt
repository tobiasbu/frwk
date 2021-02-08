
####################################
# ROOT HEADERS
####################################

set(ROOT_INC
	${PURPUR_INC}/purpur.hpp
)

source_group("Root/" FILES ${ROOT_INC})

####################################
# CORE
####################################

set(INCPATH "${PURPUR_INC}/core")
set(SRCPATH "${PURPUR_SRC}/core")


set(CORE_INC
	${INCPATH}/types.hpp
	${INCPATH}/version.hpp
	${INCPATH}/config.hpp
	${INCPATH}/export.hpp
)

set(CORE_SUB_INC
	${INCPATH}/config/api.hpp
	${INCPATH}/config/platform.hpp
	${INCPATH}/config/compiler_features.hpp

	${INCPATH}/utils/noncopyable.hpp
	${INCPATH}/utils/helper_macros.hpp
	${INCPATH}/utils/type_traits.hpp

	${INCPATH}/error/exception.hpp

	${INCPATH}/assert/assert.hpp
	${INCPATH}/assert/assert_handler.hpp
	${INCPATH}/assert/assertion_exception.hpp
	${INCPATH}/debug/breakpoint.hpp

)

set(CORE_SUB_SRC
	${SRCPATH}/error/exception.cpp

	${SRCPATH}/debug/logger.cpp

	${SRCPATH}/assert/assert_handler.cpp
	${SRCPATH}/assert/assertion_exception.cpp
)

# root folder
source_group("Header Files/" FILES ${CORE_INC})

# sub folders
source_group(TREE ${INCPATH} FILES ${CORE_SUB_INC} PREFIX "Header Files")
source_group(TREE ${SRCPATH} FILES ${CORE_SUB_SRC} PREFIX "Source Files")

ppr_add_library(purpurina_core
				SOURCES ${ROOT_INC} ${CONFIG_INC}
				${CORE_INC} ${CORE_SUB_INC} ${CORE_SUB_SRC}
)
