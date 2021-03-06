
#if defined(__GXX_EXPERIMENTAL_CXX0X__) && __GNUC__ * 10 + __GNUC_MINOR__ >= 46
	#define CT_CXX11_HAS_NOEXCEPT
#endif

#define NOINLINE __attribute__((noinline))
#define __CT_FORCEINLINE __attribute__((__always_inline__))
