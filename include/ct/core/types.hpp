
#ifndef _CHRONOTRIX_FRWK_TYPES_HPP_
#define _CHRONOTRIX_FRWK_TYPES_HPP_

namespace ct {

	////////////////////////////////////////////////////////////
	/// @defgroup Types Basic types
	/// Define portable fixed-size types
	///
	/// @{
	///
	////////////////////////////////////////////////////////////

	typedef signed char i8;   ///< 8-bit integer
	typedef unsigned char u8; ///< unsigned 8-bit integer

	typedef signed short i16;   ///< 16-bit integer
	typedef unsigned short u16; ///< unsigned 16-bit integer

	typedef signed int i32;   ///< 32-bit integer
	typedef unsigned int u32; ///< unsigned 32-bit integer

	#if defined(_MSC_VER)
	typedef signed __int64 i64;   ///< 64-bit integer
	typedef unsigned __int64 u64; ///< unsigned 64-bit integer
	#else
	typedef signed long long i64;   ///< 64-bit integer
	typedef unsigned long long u64; ///< unsigned 64-bit integer
	#endif

	typedef float f32;  ///< single precision floating point
	typedef double f64; ///<! double precision floating point

	typedef unsigned char byte; ///< Byte representation
	typedef const char * cstr;  ///< C-string

	/// @}

} // namespace ct

#endif

////////////////////////////////////////////////////////////
/// @file types.hpp
/// All "common" platforms use the same size for char, short and int
///	(basically there are 3 types for 3 sizes, so no other match is possible),
///	 we can use them without doing any kind of check
/// @ingroup core
///
////////////////////////////////////////////////////////////
