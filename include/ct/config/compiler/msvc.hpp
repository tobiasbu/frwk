
#if _MSC_FULL_VER >= 190024210 && __cplusplus != 201103L
	#define CT_CXX11_HAS_CONSTEXPR
#endif

#if _MSC_FULL_VER >= 190023026
	#define CT_CXX_HAS_NOEXCEPT
#endif

#if _MSC_FULL_VER >= 180020827
    /// Check if a function can have `= delete`
	#define CT_CXX11_DELETE_FUNCTIONS
    /// Check if a function can have `= default`
	#define CT_CXX11_DEFAULT_FUNCTIONS
#endif

#define NOINLINE __declspec(noinline)
