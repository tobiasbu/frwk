
# Detect OS
if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	set(CT_OS_WINDOWS 1)

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
	set(SFML_OS_UNIX 1)
	# if(NOT ANDROID)

	# endif()

	set(CT_OS_LINUX 1)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
	set(CT_OS_MACOSX 1)
endif()

# Check compiler
if (MSVC)
	set(CT_COMPILER_MSVC 1)
endif()
