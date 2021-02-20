
#ifndef _CHRONOTRIX_FRWK_CONTEXT_CONFIG_HPP_
#define _CHRONOTRIX_FRWK_CONTEXT_CONFIG_HPP_

#include <ct/core/types.hpp>

namespace ct {

	struct ContextConfig {
		uint8 colorBits;   // 16, 24, 32
		uint8 depthBits;   // 8, 16, 24
		uint8 stencilBits; // 8
		uint8 antiAliasLevel;
		bool doubleBuffer;

		explicit ContextConfig(uint8 colorBits = 24,
		                       uint8 depthBits = 16,
		                       uint8 stencilBits = 0,
		                       uint8 antiAliasLevel = 0,
		                       bool doubleBuffer = true)
		: colorBits(colorBits),
		  depthBits(depthBits),
		  stencilBits(stencilBits),
		  antiAliasLevel(antiAliasLevel),
		  doubleBuffer(doubleBuffer) {}
	};

} // namespace ct

#endif
