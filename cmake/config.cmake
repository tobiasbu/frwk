
# Detect OS
if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	set(PPR_OS_WINDOWS 1)

	 # detect the architecture (note: this test won't work for cross-compilation)
	#  check_type_size(void* SIZEOF_VOID_PTR)
	#  if(${SIZEOF_VOID_PTR} STREQUAL "4")
	# 	 set(ARCH_32BITS 1)
	#  elseif(${SIZEOF_VOID_PTR} STREQUAL "8")
	# 	 set(ARCH_64BITS 1)
	#  else()
	# 	 message(FATAL_ERROR "Unsupported architecture")
	# 	 return()
	#  endif()
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	set(PPR_OS_LINUX 1)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
	set(PPR_OS_MACOSX 1)
endif()

# Check compiler
if (MSVC)
	set(PPR_COMPILER_MSVC 1)
endif()
