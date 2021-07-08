
#define CT_GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)


#if defined(CT_CXX11)


	#if (CT_GCC_VERSION >= 40400)
		#define CT_CXX11_DEFAULT_FUNCTIONS
		#define CT_CXX11_DELETE_FUNCTIONS
	#endif

	#if (CT_GCC_VERSION >= 40600)
		#define CT_CXX11_HAS_NOEXCEPT
		#define CT_CXX11_NULLPTR
	#endif

	#if (CT_GCC_VERSION >= 40700)
		#define CT_CXX11_HAS_CONSTEXPR
	#endif



#endif



#define NOINLINE __attribute__((noinline))
#define __CT_FORCEINLINE __attribute__((always_inline)) inline
