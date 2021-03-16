
#ifndef _CHRONOTRIX_FRWK_CORE_UNIQUE_PTR_HPP_
#define _CHRONOTRIX_FRWK_CORE_UNIQUE_PTR_HPP_

#include <ct/core/utils/type_traits.hpp>
#include <ct/core/utils/noncopyable.hpp>
#include <ct/config.hpp>

namespace ct {

	namespace detail {
		template<class T, class D>
		struct get_pointer_deleter_type {
			using type = T*;
		};
	}

	template<class T, class D>
	class unique_ptr : noncopyable {

		using pointer = typename detail::get_pointer_deleter_type<T, remove_reference_t<D>>::type;
		using element_type = T;
    	using deleter_type = D;

		private:

			void * _pointer;

		public:

		CONSTEXPR unique_ptr() NOEXCEPT;
		CONSTEXPR unique_ptr(unique_ptr && other) NOEXCEPT;
		explicit CONSTEXPR unique_ptr(pointer ptr) NOEXCEPT;

	};

}


#endif
