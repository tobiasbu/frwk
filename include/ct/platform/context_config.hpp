
#ifndef _CHRONOTRIX_FRWK_CONTEXT_CONFIG_HPP_
#define _CHRONOTRIX_FRWK_CONTEXT_CONFIG_HPP_

#include <ct/config/types.hpp>

namespace ct {

	struct ContextConfig {
		u8 color_bits;   // 16, 24, 32
		u8 depth_bits;   // 8, 16, 24
		u8 stencil_bits; // 8
		u8 antialias_level;
		bool double_buffer;
		u8 major_version;
		u8 minor_version;

		explicit ContextConfig(u8 color_bits = 24,
		                       u8 depth_bits = 16,
		                       u8 stencil_bits = 0,
		                       u8 antialias_level = 0,
		                       bool double_buffer = true)
		: color_bits(color_bits),
		  depth_bits(depth_bits),
		  stencil_bits(stencil_bits),
		  antialias_level(antialias_level),
		  double_buffer(double_buffer) {
			major_version = 3;
			minor_version = 0;
		}
	};

} // namespace ct

#endif
