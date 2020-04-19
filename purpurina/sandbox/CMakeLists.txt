
set(INCPATH "${PURPURINA_PACKAGES_DIR}/sandbox/include/purpurina/Sandbox")
set(SRCPATH "${PURPURINA_PACKAGES_DIR}/sandbox/src/purpurina/Sandbox")



file(GLOB_RECURSE SANDBOX_SRC
	"${SRCPATH}/*.cpp"
)

file(GLOB_RECURSE SANDBOX_INC
	"${INCPATH}/**/*.hpp"
)

ppr_make_source_groups(INCLUDES ${SANDBOX_INC}
					   INCLUDE_DIR ${INCPATH}
					   SOURCES ${SANDBOX_SRC}
)

# Create sandbox executable
ppr_add_executable(sandbox SOURCES ${SANDBOX_SRC} ${SANDBOX_INC})
