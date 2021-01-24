
#ifndef _PURPURINA_COMPILER_FEATURES_HPP_
#define _PURPURINA_COMPILER_FEATURES_HPP_

	#if (defined (__cplusplus) && (__cplusplus > 199711L)) || (defined(_MSC_FULL_VER) && (_MSC_FULL_VER >= 150020706))
		#define PPR_CXX11
	#endif

	////////////////////////////////////////////////////////////
	// Define NULLPTR macro
	////////////////////////////////////////////////////////////
	#ifdef PPR_CXX11
		/// Null pointer
		#define NULLPTR nullptr
	#else
		/// Null pointer
		#define NULLPTR 0
	#endif

	////////////////////////////////////////////////////////////
	// Define NOEXCEPT macro
	////////////////////////////////////////////////////////////
	#ifndef NOEXCEPT
		// https://bcain-llvm.readthedocs.io/projects/clang/en/release_38/LanguageExtensions/
		#ifdef __clang__
			#if __has_feature(cxx_noexcept)
				#define __PPR_HAS_NOEXCEPT
			#endif
		#endif
	#endif

	#ifdef __PPR_HAS_NOEXCEPT
		/// noexcept
		#define NOEXCEPT noexcept
	#else
		/// noexcept
		#define NOEXCEPT
	#endif

#endif
