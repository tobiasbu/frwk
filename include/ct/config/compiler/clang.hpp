
// https://bcain-llvm.readthedocs.io/projects/clang/en/release_38/LanguageExtensions/

#if __has_feature(cxx_constexpr)
	#define CT_CXX11_HAS_CONSTEXPR
#endif

#if __has_feature(cxx_noexcept)
	#define CT_CXX11_HAS_NOEXCEPT
#endif

/// Check if a function can have `= default`
#if __has_feature(cxx_defaulted_functions)
	#define CT_CXX11_DEFAULT_FUNCTIONS
#endif

#if __has_feature(cxx_deleted_functions)
	#define CT_CXX11_DELETE_FUNCTIONS
#endif

#define NOINLINE __attribute__((noinline))
#define __CT_FORCEINLINE __attribute__((__always_inline__))
