
#ifndef _CHRONOTRIX_FRWK_CONTEXT_CONFIG_HPP_
#define _CHRONOTRIX_FRWK_CONTEXT_CONFIG_HPP_

#include <ct/core/types.hpp>

namespace ct {



	struct ContextConfig {
		uint8 color_bits;   // 16, 24, 32
		uint8 depth_bits;   // 8, 16, 24
		uint8 stencil_bits; // 8
		uint8 antialias_level;
		bool double_buffer;
		uint8 major_version;
		uint8 minor_version;

		explicit ContextConfig(uint8 color_bits = 24,
		                       uint8 depth_bits = 16,
		                       uint8 stencil_bits = 0,
		                       uint8 antialias_level = 0,
		                       bool double_buffer = true)
		: color_bits(color_bits),
		  depth_bits(depth_bits),
		  stencil_bits(stencil_bits),
		  antialias_level(antialias_level),
		  double_buffer(double_buffer) {}
	};

} // namespace ct

#endif
