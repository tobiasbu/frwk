
file(GLOB_RECURSE CORE_SRC
	"${PURPURINA_SOURCES_PATH}/Core/*.cpp"
)

file(GLOB_RECURSE CORE_INC
	"${PURPURINA_INCLUDES_PATH}/Core/*.hpp"
)

# Create source groups (aka Filters)
message("Core dir: " ${CMAKE_CURRENT_SOURCE_DIR})
source_group(TREE "${PROJECT_SOURCE_DIR}/src/purpurina/Core" FILES ${CORE_SRC} PREFIX "Source Files")
source_group(TREE "${PROJECT_SOURCE_DIR}/include/purpurina/Core" FILES ${CORE_INC} PREFIX "Header Files")
# source_group(TREE ${CORE_SRC} PREFIX )
# source_group("Header Files\\" FILES ${CORE_INC})


# Create the Library
add_library(purpurina-core ${CORE_SRC} ${CORE_INC})

set_target_properties(purpurina-core PROPERTIES DEFINE_SYMBOL PURPURINA_CORE_EXPORTS)

 # set the target's folder (for IDEs that support it, e.g. Visual Studio)
# set_target_properties(purpurina-core PROPERTIES FOLDER "purpurina")

# add <purpurina/include/../../> as public include directory
target_include_directories(purpurina-core
						   PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)

 target_include_directories(purpurina-core INTERFACE $<INSTALL_INTERFACE:include>)



# target_include_directories(purpurina-core PUBLIC ${CORE_INC} "Purpurina/Core")

# Link to Main Library
target_link_libraries(purpurina-core PUBLIC Purpurina)
