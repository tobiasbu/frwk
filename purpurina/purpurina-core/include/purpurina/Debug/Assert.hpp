

#ifndef _PURPURINA_ASSERT_HPP_
#define _PURPURINA_ASSERT_HPP_

#include <purpurina/Export.hpp>
#include <purpurina/Config.hpp>


	#define PURPURINA_ASSERT_FILE __FILE__
	#define PURPURINA_ASSERT_LINE __LINE__

	// Assert function macro
	//#if defined(__GNUC__) || defined(__clang__)
	//	#define PURPURINA_ASSERT_FUNC __PRETTY_FUNCTION__
	//#elif defined(_MSC_VER)
	//	#define PURPURINA_ASSERT_FUNC __FUNCSIG__
	//#elif defined(__SUNPRO_CC)
	//	#define PURPURINA_ASSERT_FUNC __func__
	//#else
	//	#define PURPURINA_ASSERT_FUNC __FUNCTION__
	//#endif

#define PURPURINA_ASSERT_BUFFER_SIZE 1024

	namespace ppr {

		namespace priv {
			PURPURINA_CORE_API void handleAssert(
				const char * expression,
				const char* file,
				int line,
				const char * messge,
				...);
		}

	#define assert(e, msg, ...) (!!e) ? (void)0 : priv::handleAssert(#e, PURPURINA_ASSERT_FILE, PURPURINA_ASSERT_LINE, msg, ##__VA_ARGS__)

	}

#endif
