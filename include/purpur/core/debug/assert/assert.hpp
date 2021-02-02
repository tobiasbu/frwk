////////////////////////////////////////////////////////////
// Purpurina Engine
//
// \todo Copyright notice
//
////////////////////////////////////////////////////////////
///
/// \ingroup purpurina-core
/// \file Assert.hpp
/// \author Tobias Ulrich <flamenco.bluegrass@gmail.com>
/// \date September 25, 2020
///
////////////////////////////////////////////////////////////

#ifndef _PURPURINA_FRWK_ASSERT_HPP_
#define _PURPURINA_FRWK_ASSERT_HPP_

#include <purpur/core/debug/assert/assert_handler.hpp>
#include <purpur/core/debug/assert/assertion_exception.hpp>
#include <purpur/core/debug/breakpoint.hpp>
#include <purpur/core/utils/helper_macros.hpp>

#ifndef __PPR_ASSERT_ENABLED
	#ifdef PPR_DEBUG
		#define __PPR_ASSERT_ENABLED
	#endif
#endif

#define PPR_ASSERT_FILE __FILE__
#define PPR_ASSERT_LINE __LINE__

#if defined(__GNUC__) || defined(__clang__)
	#define PPR_ASSERT_FUNCTION __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
	#define PPR_ASSERT_FUNCTION __FUNCSIG__
#elif defined(__SUNPRO_CC)
	#define PPR_ASSERT_FUNCTION __func__
#else
	#define PPR_ASSERT_FUNCTION __FUNCTION__
#endif

#define PURPURINA_APPLY_VA_ARGS(M, ...) PURPURINA_DO_APPLY_VA_ARGS(M, (__VA_ARGS__))
#define PURPURINA_DO_APPLY_VA_ARGS(M, args) M args

#define PURPURINA_ASSERT_NARG(...)                                                               \
	PURPURINA_APPLY_VA_ARGS(PURPURINA_ASSERT_NARG_, PPR_NO_MACRO, ##__VA_ARGS__, 32, 31, 30, 29, \
	                        28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12,  \
	                        11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, PPR_NO_MACRO)
#define PURPURINA_ASSERT_NARG_(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, \
                               _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, \
                               _28, _29, _30, _31, _32, _33, ...)                               \
	_33

#define PURPURINA_HAS_ONE_ARGUMENT(...)                                                            \
	PURPURINA_APPLY_VA_ARGS(PURPURINA_ASSERT_NARG_, PPR_NO_MACRO, ##__VA_ARGS__, 0, 0, 0, 0, 0, 0, \
	                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   \
	                        0, 0, 1, 0, PPR_NO_MACRO)

#define __PPR_ASSERT_(debug, ...)                                    \
	PPR_JOIN(__PPR_ASSERT_, PURPURINA_HAS_ONE_ARGUMENT(__VA_ARGS__)) \
	(debug, __VA_ARGS__)
#define __PPR_ASSERT_0(debug, ...) PURPURINA_APPLY_VA_ARGS(__PPR_ASSERT_2, debug, __VA_ARGS__)
#define __PPR_ASSERT_1(debug, expression) __PPR_ASSERT_2(debug, expression, PPR_NULLPTR)

////////////////////////////////////////////////////////////
/// \brief Assert given expression
///
/// \param expression Expression to be tested
/// \param message Optional message
/// \param args Additional message args
///
/// \exception ppr::AssertException
///
////////////////////////////////////////////////////////////
#define PPR_ASSERT(expression, ...) __PPR_ASSERT_(true, expression, __VA_ARGS__)

#if defined(_MSC_FULL_VER) && (_MSC_FULL_VER >= 140050215)

	#define __PPR_ASSERT_3(debug, expression, ...)                                            \
		__pragma(warning(push)) __pragma(warning(disable : 4127)) do {                        \
			static bool _ignore = false;                                                      \
			if ((! ! expression) || _ignore || ppr::internal::Assert::ignoreAllAsserts())     \
				void(0);                                                                      \
			else {                                                                            \
				ppr::internal::Assert::Action action = ppr::internal::Assert::getAction();    \
				ppr::cstr message = ppr::internal::Assert::handle(                            \
				PPR_ASSERT_FILE, PPR_ASSERT_LINE, PPR_ASSERT_FUNCTION, #expression, &_ignore, \
				__VA_ARGS__);                                                                 \
				if (action == ppr::internal::Assert::Action::Break) {                         \
					PPR_BREAKPOINT();                                                         \
				} else if (action == ppr::internal::Assert::Action::Throw) {                  \
					throw ppr::AssertionException(PPR_ASSERT_FILE, PPR_ASSERT_LINE,           \
					                              PPR_ASSERT_FUNCTION, #expression, message); \
				}                                                                             \
			}                                                                                 \
		}                                                                                     \
		while (false)                                                                         \
		__pragma(warning(pop))

#endif

#undef __PPR_ASSERT_2

#ifdef __PPR_ASSERT_ENABLED
	#define __PPR_ASSERT_2(debug, expression, ...) __PPR_ASSERT_3(debug, expression, __VA_ARGS__)
#else
	#define __PPR_ASSERT_2(debug, expression, ...) (void)(true ? (void)0 : ((void)(expression)))
#endif

#endif
