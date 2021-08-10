

#ifndef _CHRONOTRIX_FRWK_CORE_TYPE_INFO_HPP_
#define _CHRONOTRIX_FRWK_CORE_TYPE_INFO_HPP_

#include <ct/config.hpp>
#include <ct/core/types/type_traits.hpp>

#define __CT_REGISTER_CTTI_INDEXERS(begin, end) \
	namespace ct { \
		namespace detail { \
			namespace ctti { \
				CT_CONSTEXPR u64 ctti_begin = begin; \
				CT_CONSTEXPR u64 ctti_end = end; \
			} \
		} \
	}

#if defined(_MSC_VER) && !defined(__clang__)
__CT_REGISTER_CTTI_INDEXERS(41, 19, false)
#elif defined(__GNUC__)
// 'static constexpr const char* ct::detail::typeinfo<T>::a() [with T =' ### ']'
__CT_REGISTER_CTTI_INDEXERS(68, 1)
#else
__CT_REGISTER_CTTI_INDEXERS(0, 0)
#endif

namespace ct {
	template <class T>
	struct type;

} // namespace ct

#define CT_REGISTER_TYPENAME(T) \
	namespace ct { \
		template <> \
		struct type<T> { \
			static CT_CONSTEXPR cstr name = #T; \
		}; \
	}

#define CT_REGISTER_TYPENAME_AS(T, type_name) \
	namespace ct { \
		template <> \
		struct type<T> { \
			static CT_CONSTEXPR cstr name = #type_name; \
		}; \
	}

namespace ct {

	namespace detail {

		namespace ctti {

			template <class It, class Iu>
			CT_CONSTEXPR inline It constexpr_search(It first1, It last1, Iu first2, Iu last2) NOEXCEPT {
				if (first2 == last2) {
					return first1; // specified in C++11
				}

				while (first1 != last1) {
					It it1 = first1;
					Iu it2 = first2;

					while (*it1 == *it2) {
						++it1;
						++it2;
						if (it2 == last2)
							return first1;
						if (it1 == last1)
							return last1;
					}

					++first1;
				}

				return last1;
			}

			template <u32 arr_size>
			CT_CONSTEXPR inline cstr remove_begin_rt(cstr start) NOEXCEPT {
				auto a = "";
				cstr const it = constexpr_search(start, start + arr_size, a, a + sizeof(a) - 1);
				return (it == start + arr_size ? start : it - 1);
			}

			template <u32 arr_size>
			CT_CONSTEXPR inline cstr remove_begin(cstr start) NOEXCEPT {
				return remove_begin_rt<arr_size - ctti_begin>(start + ctti_begin);
			}

		} // namespace ctti

		class str_portion {
		private:
			cstr _str;
			u64 _size;

		public:
			static CT_CONSTEXPR auto npos {static_cast<u64>(-1)};

			str_portion() = default;
			CT_CONSTEXPR str_portion(cstr source_str, u64 size) NOEXCEPT : _str(source_str), _size(size) {}

			template <u64 arr_size>
			CT_CONSTEXPR str_portion(const char (&source_str)[arr_size]) NOEXCEPT : _str(source_str),
			                                                                        _size(arr_size - 1) {}

			template <u64 arr_size>
			CT_CONSTEXPR str_portion(cstr str) NOEXCEPT : _str(str), _size(arr_size) {}

			CT_CONSTEXPR cstr data() const NOEXCEPT {
				return _str;
			}

			NODISCARD CT_CONSTEXPR str_portion subview(const u64 offset = 0, u64 count = npos) const {
				// TODO: check offset and clamp count
				return str_portion(_str + offset, count);
			}
		};

		template <class T>
		struct typeinfo {
			CT_CONSTEXPR static const char * a() NOEXCEPT {
				str_portion part(CT_CURRENT_FUNCTION);
				return part.subview(ctti::ctti_begin).data();
			}
		};

	} // namespace detail

	template <class T>
	NODISCARD CT_CONSTEXPR inline cstr type_name() NOEXCEPT {
		typedef typename remove_reference<T>::type no_ref;
		if CT_CONSTEXPR (is_type_complete<type<no_ref>>) {
			using registered = std::decay_t<decltype(*static_cast<type<no_ref>*>(CT_NULLPTR))>;
			return registered::name;
		}
		return detail::typeinfo<no_ref>::a();
	}
} // namespace ct

CT_REGISTER_TYPENAME(i32)
CT_REGISTER_TYPENAME(u32)
CT_REGISTER_TYPENAME(f32)
CT_REGISTER_TYPENAME(u64)

#endif
