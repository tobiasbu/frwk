
#ifndef _CHRONOTRIX_FRWK_MATH_RECT_HPP_
#define _CHRONOTRIX_FRWK_MATH_RECT_HPP_

#include <ct/config/types.hpp>
#include <ct/math/detail/trect.hpp>

namespace ct {

	typedef trect<f32> rect;   ///< Rectangle of float
	typedef trect<i32> recti;  ///< Rectangle of 32-bit integer
	typedef trect<u32> rectu;  ///< Rectangle of unsigned 32-bit integer

}



#endif
