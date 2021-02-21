////////////////////////////////////////////////////////////
// Chronotrix Framework
//
// \todo Copyright notice
//
////////////////////////////////////////////////////////////
///
/// \ingroup chronotrix-core
/// \file Assert.hpp
/// \author Tobias Ulrich <flamenco.bluegrass@gmail.com>
/// \date September 25, 2020
///
////////////////////////////////////////////////////////////

#ifndef _CHRONOTRIX_FRWK_ASSERT_HPP_
#define _CHRONOTRIX_FRWK_ASSERT_HPP_

#include <ct/core/assert/assert_handler.hpp>
#include <ct/core/assert/assertion_exception.hpp>
#include <ct/core/debug/breakpoint.hpp>
#include <ct/core/utils/helper_macros.hpp>

#ifndef __CT_ASSERT_ENABLED
	#ifdef CT_DEBUG
		#define __CT_ASSERT_ENABLED
	#endif
#endif

#define CT_ASSERT_FILE __FILE__
#define CT_ASSERT_LINE __LINE__

#if defined(__GNUC__) || defined(__clang__)
	#define CT_ASSERT_FUNCTION __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
	#define CT_ASSERT_FUNCTION __FUNCSIG__
#elif defined(__SUNPRO_CC)
	#define CT_ASSERT_FUNCTION __func__
#else
	#define CT_ASSERT_FUNCTION __FUNCTION__
#endif

// clang-format off

#define CT_APPLY_VA_ARGS(M, ...) __CT_DO_APPLY_VA_ARGS(M, (__VA_ARGS__))
#define __CT_DO_APPLY_VA_ARGS(M, args) M args

#define CT_ASSERT_NARG(...) CT_APPLY_VA_ARGS(__CT_ASSERT_NARG_,				   \
	CT_NO_MACRO, ##__VA_ARGS__,										   						   \
	32, 31, 30, 29, 28, 27, 26, 25,										   						   \
	24, 23, 22, 21, 20, 19, 18, 17,										   						   \
	16,	15, 14, 13, 12, 11, 10,  9,										   						   \
	 8,  7,  6,  5,  4,  3,  2,  1,										   						   \
	 0, CT_NO_MACRO)										   						               \

#define __CT_ASSERT_NARG_( _0, _1, _2, _3, _4, _5, _6, _7, _8,								   \
                                _9, _10, _11, _12, _13, _14, _15, _16,							   \
                               _17, _18, _19, _20, _21, _22, _23, _24,							   \
                               _25, _26, _27, _28, _29, _30, _31, _32, _33, ...) _33

#define CT_HAS_ONE_ARGUMENT(...) CT_APPLY_VA_ARGS(__CT_ASSERT_NARG_,            \
	CT_NO_MACRO, ##__VA_ARGS__,										   						   \
    0, 0, 0, 0, 0, 0, 0, 0,										   						   		   \
	0, 0, 0, 0, 0, 0, 0, 0,																		   \
	0, 0, 0, 0, 0, 0, 0, 0,																		   \
	0, 0, 0, 0, 0, 0, 0, 1,																		   \
	0, CT_NO_MACRO)																		   	   \


////////////////////////////////////////////////////////////
/// \brief Assert given expression
///
/// \param expression Expression to be tested
/// \param message Optional message
/// \param args Additional message args
///
/// \exception ct::AssertException
///
////////////////////////////////////////////////////////////
#define CT_ASSERT(expression, ...) __CT_ASSERT_(true, expression, __VA_ARGS__)

#define __CT_ASSERT_(debug, ...)			CT_JOIN(__CT_ASSERT_, CT_HAS_ONE_ARGUMENT(__VA_ARGS__))(debug, __VA_ARGS__)
#define __CT_ASSERT_0(debug, ...)			CT_APPLY_VA_ARGS(__CT_ASSERT_2, debug, __VA_ARGS__)
#define __CT_ASSERT_1(debug, expression)  	__CT_ASSERT_2(debug, expression, NULLPTR)

#if defined(_MSC_FULL_VER) && (_MSC_FULL_VER >= 140050215)

	#define __CT_ASSERT_3(debug, expression, ...)											  \
		__pragma(warning(push))													  		      \
		__pragma(warning(disable : 4127)) 													  \
		do {                                                      							  \
			static bool _ignore = false;                                                      \
			if (expression || ct::internal::Assert::ignore_all_asserts())    			      \
				void(0);                                                                      \
			else {                                                                            \
				ct::internal::Assert::Action action = ct::internal::Assert::get_action();     \
				ct::cstr message = ct::internal::Assert::handle(					          \
					CT_ASSERT_FILE, CT_ASSERT_LINE, CT_ASSERT_FUNCTION,                    	  \
					#expression, 													          \
					&_ignore,															      \
					__VA_ARGS__);															  \
																						      \
				if (action == ct::internal::Assert::Action::Break) {                          \
					CT_BREAKPOINT();                                                          \
				} else if (action == ct::internal::Assert::Action::Throw) {                   \
					throw ct::AssertionException(CT_ASSERT_FILE, CT_ASSERT_LINE,              \
					                              CT_ASSERT_FUNCTION, #expression, message);  \
				}                                                                             \
			}                                                                                 \
		}                                                                                     \
		while (false)                                                                         \
		__pragma(warning(pop))

#endif

// clang-format on

#undef __CT_ASSERT_2

#ifdef __CT_ASSERT_ENABLED
	#define __CT_ASSERT_2(debug, expression, ...) __CT_ASSERT_3(debug, expression, __VA_ARGS__)
#else
	#define __CT_ASSERT_2(debug, expression, ...) (void)(true ? (void)0 : ((void)(expression)))
#endif

#endif
