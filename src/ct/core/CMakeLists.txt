
####################################
# ROOT HEADERS
####################################

set(ROOT_INC ${CT_INC}/ct.hpp)
ct_group(${ROOT_INC} TREE ${CT_INC} NAME "")

####################################
# CORE
####################################

# includes
ct_file_list(ROOT ${INCPATH} OUTPUT INC
	types.hpp
	version.hpp
	config.hpp
	export.hpp
)
ct_group(${INC})

# includes subfolder
ct_file_list(ROOT ${INCPATH} OUTPUT SUB_INC
    config/api.hpp
	config/os_detection.hpp
	config/compiler_features.hpp
	utils/noncopyable.hpp
	utils/helper_macros.hpp
	utils/type_traits.hpp
	error/exception.hpp
	assert/assert.hpp
	assert/assert_handler.hpp
	assert/assertion_exception.hpp
	debug/breakpoint.hpp
)
ct_group(${SUB_INC} TREE ${INCPATH})

# sources subfolder
ct_file_list(ROOT ${SRCPATH} OUTPUT SUB_SRC
	error/exception.cpp
	debug/logger.cpp
	assert/assert_handler.cpp
	assert/assertion_exception.cpp
)
ct_group(${SUB_SRC} TREE ${SRCPATH} IS_IMPL)


# make library target
ct_add_library(chronotrix_core
				SOURCES ${INC} ${SUB_INC} ${SUB_SRC} ${ROOT_INC}
)
