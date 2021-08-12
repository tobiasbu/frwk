
#ifndef _CHRONOTRIX_FRWK_TYPE_TRAITS_TRANSFORMATION_HPP_
#define _CHRONOTRIX_FRWK_TYPE_TRAITS_TRANSFORMATION_HPP_

#include <ct/core/type/traits/is_array.hpp>
#include <ct/core/type/traits/is_function.hpp>
#include <ct/core/type/traits/remove_reference.hpp>
#include <ct/core/type/traits/modifications.hpp>

namespace ct {

	template <typename T>
	class decay {
	private:
		using __no_ref = remove_reference_t<T>;

		template <typename U,
		          bool IsArray = is_array<U>::value,
		          bool IsFunction = is_function<U>::value>
		struct __decay_selector;

		template <typename U>
		struct __decay_selector<U, false, false> {
			using __type = remove_cv_t<U>;
		};

		template <typename U>
		struct __decay_selector<U, true, false> {
			using __type = remove_extent_t<U>;
		};

		template <typename U>
		struct __decay_selector<U, false, true> {
			using __type = add_pointer_t<U>;
		};

	public:
		using type = typename __decay_selector<__no_ref>::__type;
	};

	template <class T>
	using decay_t = typename decay<T>::type;

	template <class...>
	struct make_void {
		using type = void;
	};

	template <class... T>
	using void_t = typename make_void<T...>::type;

	template <class T, typename = void>
	CT_CONSTEXPR bool is_type_complete = false;

	template <class T>
	CT_CONSTEXPR bool is_type_complete<T, void_t<decltype(sizeof(T))>> = true;

	template <typename T, typename TLambda>
	bool call_if_defined(TLambda && lambda) {
		if CT_CONSTEXPR (is_type_complete<T>) {
			lambda(static_cast<T *>(CT_NULLPTR));
			return true;
		}
		return false;
	}

} // namespace ct

#endif