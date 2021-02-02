
#ifndef _PURPURINA_FRWK_COMPILER_FEATURES_HPP_
#define _PURPURINA_FRWK_COMPILER_FEATURES_HPP_

#if defined(__cplusplus)
	#if (__cplusplus > 199711L) || (defined(_MSC_FULL_VER) && (_MSC_FULL_VER >= 150020706))
		#define PPR_CXX11
	#endif

	#if __cplusplus >= 201402L
		#define PPR_CXX14
	#endif

	#if __cplusplus >= 201703L
		#define PPR_CXX17
	#endif

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
// Define CONSTEXPR macro
////////////////////////////////////////////////////////////
#if (_MSC_FULL_VER >= 190024210)
	/// Constant expression
	#define CONSTEXPR constexpr
#else
	#define CONSTEXPR
#endif

////////////////////////////////////////////////////////////
// Define NOEXCEPT macro
////////////////////////////////////////////////////////////
#ifndef NOEXCEPT
	// https://bcain-llvm.readthedocs.io/projects/clang/en/release_38/LanguageExtensions/
	#ifdef __clang__
		#if __has_feature(cxx_noexcept)
			#define PPR_CXX11_HAS_NOEXCEPT
		#endif
	#elif defined(__GXX_EXPERIMENTAL_CXX0X__) && __GNUC__ * 10 + __GNUC_MINOR__ >= 46
		#define PPR_CXX11_HAS_NOEXCEPT
	#else defined(_MSC_FULL_VER) && _MSC_FULL_VER >= 190023026
		#define PPR_CXX11_HAS_NOEXCEPT
	#endif
#endif

#ifdef PPR_CXX11_HAS_NOEXCEPT
	/// noexcept
	#define NOEXCEPT noexcept
#else
	/// noexcept
	#define NOEXCEPT
#endif

////////////////////////////////////////////////////////////
#if defined(_MSC_FULL_VER) && _MSC_FULL_VER >= 180020827
	/// Check if a function can have `= delete`
	#define PPR_CXX11_DELETE_FUNCTIONS
	/// Check if a function can have `= default`
	#define PPR_CXX11_DEFAULT_FUNCTIONS
#endif

#endif
