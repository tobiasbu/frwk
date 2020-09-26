
set(INCPATH "${PURPURINA_PACKAGES_DIR}/purpurina-core/include/purpurina")
set(SRCPATH "${PURPURINA_PACKAGES_DIR}/purpurina-core/src/purpurina")

set(CORE_INC_CONFIG
	"${INCPATH}/Config.hpp"
	"${INCPATH}/Export.hpp"
	"${PURPURINA_PACKAGES_DIR}/purpurina-core/include/purpurina/Purpurina.hpp"
)

file(GLOB_RECURSE CORE_INC
	"${INCPATH}/Macros/HelperMacros.hpp"
	"${INCPATH}/Error/Exception.hpp"
	"${INCPATH}/Debug/Assert/Assert.hpp"
	"${INCPATH}/Debug/Assert/AssertHandler.hpp"
	"${INCPATH}/Debug/Assert/AssertionException.hpp"
	"${INCPATH}/Debug/Break.hpp"
	"${INCPATH}/**/*.hpp"
)


set(CORE_SRC
	"${SRCPATH}/Error/Exception.cpp"
	"${SRCPATH}/Debug/Logger.cpp"
	"${SRCPATH}/Debug/Assert/AssertHandler.cpp"
	"${SRCPATH}/Debug/Assert/AssertionException.cpp"
)

# file(GLOB_RECURSE CORE_SRC
# 	"${SRCPATH}/**/*.cpp"
# )


source_group("Header Files/" FILES ${CORE_INC_CONFIG})

source_group(TREE ${INCPATH} FILES ${CORE_INC} PREFIX "Header Files")
source_group(TREE ${SRCPATH} FILES ${CORE_SRC} PREFIX "Source Files")


ppr_add_library(purpurina-core
			    SOURCES ${CORE_INC} ${CORE_INC_CONFIG} ${CORE_SRC}
)
