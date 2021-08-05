////////////////////////////////////////////////////////////
// Chronotrix Framework
//
// @todo Copyright notice
//
////////////////////////////////////////////////////////////

#ifndef _CHRONOTRIX_FRWK_HELPER_MACROS_
	#define _CHRONOTRIX_FRWK_HELPER_MACROS_

    /////////////////////////////////////////////////
    /// @brief Convert macro parameter to string literal.
    ///
    /// @code
    /// 	auto a = CT_STRINGER(3);
    /// @endcode
    ///
    /// @param X Value to be stringized
    /// @return Stringized value
    ///
    /////////////////////////////////////////////////
	#define CT_STRINGER(X) __CT_DO_STRINGER(X)
	#define __CT_DO_STRINGER(X) #X

    ////////////////////////////////////////////////////////////
    /// @brief Join two macro arguments together.
    ///
    /// @param X First argument
    /// @param Y Second argument
    /// @return Joined values
    ///
    ////////////////////////////////////////////////////////////
	#define CT_JOIN(X, Y) __CT_DO_JOIN(X, Y)
	#define __CT_DO_JOIN(X, Y) __CT_DO_JOIN2(X, Y)
	#define __CT_DO_JOIN2(X, Y) X##Y

    /**
     * @brief Returns the number of arguments that have been
     * passed to it.
     *
     * Using this helper inside of a macro with pre-defined arguments (ex: MACRO(arg, ...))
     * it will counted only the variadic paramenters.
     *
     * Example:
     * #define MY_MACRO(...)      5   			CT_ARGS_COUNT(__VA_ARGS__)
     * #define MY_MACRO_WITH_ARG(arg1, ...)     CT_ARGS_COUNT(__VA_ARGS__)
     *
     * MY_MACRO() // returns 0
     * MY_MACRO(1, abc) // returns 2
     * MY_MACRO(1, def, 3.14) // returns 3
     *
     * MY_MACRO_WITH_ARG(arg) // returns 0
     * MY_MACRO_WITH_ARG(arg, 1) // returns 1
     * MY_MACRO_WITH_ARG(arg, 1, abc) // returns 2
     *
     *
     * @see https://groups.google.com/g/comp.std.c/c/d-6Mj5Lko_s?pli=1
     */
	#define CT_ARGS_COUNT(...) __CT_DO_ARGS_COUNT(CT_NO_MACRO, ##__VA_ARGS__, __CT_RSEQ_N)
	#define __CT_DO_ARGS_COUNT(...) __CT_NARG(__VA_ARGS__)

// clang-format off

	#define __CT_RSEQ_N \
                                62, 61, 60, \
    59, 58, 57, 56, 55, 54, 53, 52, 51, 50, \
    49, 48, 47, 46, 45, 44, 43, 42, 41, 40, \
    39, 38, 37, 36, 35, 34, 33, 32, 31, 30, \
    29, 28, 27, 26, 25, 24, 23, 22, 21, 20, \
    19, 18, 17, 16, 15, 14, 13, 12, 11, 10, \
     9,  8,  7,  6,  5,  4,  3,  2,  1,  0


	#define __CT_NARG( \
	_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, \
	_11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
	_21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
	_31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
	_41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
	_51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
	_61,_62,_63, \
	N, ...) N


	#define CT_FORWARD(M, ...) M(__VA_ARGS__)

	/**
	* @brief Get 2th VA_ARG
	*/
	#define CtGet_VA_ARG_2(...) __CtGet_DO_VA_ARG_2(CT_NO_MACRO, ##__VA_ARGS__, __CT_RSEQ_N)
	#define __CtGet_DO_VA_ARG_2(...) __CtGet_DO_VA_ARG_2_(__VA_ARGS__)
	#define __CtGet_DO_VA_ARG_2_( \
		_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, \
		_11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
		_21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
		_31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
		_41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
		_51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
		_61,_62,_63, N, ...) _2




#endif

////////////////////////////////////////////////////////////
/// @file helper_macros.hpp
/// @ingroup core
/// @author Tobias Ulrich <flamenco.bluegrass@gmail.com>
/// @date September 14, 2020
///
////////////////////////////////////////////////////////////
