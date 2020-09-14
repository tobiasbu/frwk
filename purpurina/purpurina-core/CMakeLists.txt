
set(INCPATH "${PURPURINA_PACKAGES_DIR}/purpurina-core/include/purpurina")
set(SRCPATH "${PURPURINA_PACKAGES_DIR}/purpurina-core/src/purpurina")

set(CORE_INC_CONFIG
	"${INCPATH}/Config.hpp"
	"${INCPATH}/Export.hpp"
	"${PURPURINA_PACKAGES_DIR}/purpurina-core/include/purpurina/Purpurina.hpp"
)

set(CORE_SRC
	"${SRCPATH}/Debug/Assert.cpp"
	"${SRCPATH}/Debug/Logger.cpp"
)

# file(GLOB_RECURSE CORE_SRC
# 	"${SRCPATH}/**/*.cpp"
# )

file(GLOB_RECURSE CORE_INC
	"${INCPATH}/**/*.hpp"
)

source_group("Header Files/" FILES ${CORE_INC_CONFIG})

source_group(TREE ${INCPATH} FILES ${CORE_INC} PREFIX "Header Files")
source_group(TREE ${SRCPATH} FILES ${CORE_SRC} PREFIX "Source Files")


ppr_add_library(purpurina-core
			    SOURCES ${CORE_INC} ${CORE_INC_CONFIG} ${CORE_SRC}
)
