
set(INCPATH "${PURPURINA_PACKAGES_DIR}/purpurina-core/include/purpurina/Core")
set(SRCPATH "${PURPURINA_PACKAGES_DIR}/purpurina-core/src/purpurina/Core")

set(CORE_INC_CONFIG
	"${INCPATH}/Config.hpp"
	"${INCPATH}/Types.hpp"
)

file(GLOB_RECURSE CORE_SRC
	"${SRCPATH}/**/*.cpp"
)

file(GLOB_RECURSE CORE_INC
	"${INCPATH}/**/*.hpp"
)

source_group("Header Files/" FILES ${CORE_INC_CONFIG})

source_group(TREE ${INCPATH} FILES ${CORE_INC} PREFIX "Header Files")
source_group(TREE ${SRCPATH} FILES ${CORE_SRC} PREFIX "Source Files")




# Create the Library
add_library(purpurina-core SHARED ${CORE_INC_CONFIG} ${CORE_SRC} ${CORE_INC})

set_target_properties(purpurina-core PROPERTIES DEFINE_SYMBOL PURPURINA_CORE_EXPORTS)

# set the target's folder (for IDEs that support it, e.g. Visual Studio)
# set_target_properties(purpurina-core PROPERTIES FOLDER "purpurina")

# add <purpurina/include/../../> as public include directory
target_include_directories(purpurina-core
						   PUBLIC $<BUILD_INTERFACE:${PURPURINA_PACKAGES_DIR}/purpurina-core/include>)

target_include_directories(purpurina-core INTERFACE $<INSTALL_INTERFACE:include>)



# target_include_directories(purpurina-core PUBLIC ${CORE_INC} "Purpurina/Core")

# Link to Main Library
# target_link_libraries(purpurina-core PUBLIC Purpurina)
