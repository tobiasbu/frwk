
#include <ct/config.hpp>
#include <ct/core/utils/type_traits.hpp>


#define __CT_REGISTER_CTTI_INDEXERS(begin, end) \
	namespace ct { \
		namespace detail { \
			namespace ctti { \
				CONSTEXPR u64 ctti_begin = begin; \
				CONSTEXPR u64 ctti_end = end; \
	}}} 



#if defined(_MSC_VER) && !defined(__clang__)
	__CT_REGISTER_CTTI_INDEXERS(41, 19)
#else
	__CT_REGISTER_CTTI_INDEXERS(0, 0)
#endif


namespace ct {
	    template <class T>
	    struct type {
		    static CONSTEXPR cstr name = "T";
	    };
}         // namespace ct

#define CT_REGISTER_TYPENAME(T) \
	namespace ct { \
		template <> \
		struct type<T> { \
			static CONSTEXPR cstr name = #T; \
		}; \
	}



namespace ct {

	namespace detail {

		namespace ctti {

			template <class It, class Iu>
			CONSTEXPR inline It
			constexpr_search(It first1, It last1, Iu first2, Iu last2) NOEXCEPT {
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
			CONSTEXPR inline cstr remove_begin_rt(cstr start) NOEXCEPT {
				auto a = "";
				cstr const it = constexpr_search(start, start + arr_size, a, a + sizeof(a) - 1);
				return (it == start + arr_size ? start : it - 1);
			}

			template <u32 arr_size>
			CONSTEXPR inline cstr remove_begin(cstr start) NOEXCEPT {
				return remove_begin_rt<arr_size - ctti_begin>(start + ctti_begin);
			}

		} // namespace ctti

		class str_portion {
			private:
			cstr _str;
			u64 _size;

			public:
			static CONSTEXPR auto npos {static_cast<u64>(-1)};

			str_portion() = default;
			CONSTEXPR str_portion(cstr source_str, u64 size) NOEXCEPT
			:
			_str(source_str),
			_size(size)
			{}

			template <u64 arr_size>
			CONSTEXPR str_portion(const char (&source_str)[arr_size]) NOEXCEPT
			:
			_str(source_str),
			_size(arr_size - 1)
			{}

			template <u64 arr_size>
			CONSTEXPR str_portion(cstr str) NOEXCEPT
			:
			_str(str),
			_size(arr_size) {}

			CONSTEXPR cstr data() const NOEXCEPT {
				return _str;
			}

			NODISCARD CONSTEXPR str_portion subview(const u64 offset = 0, u64 count = npos) const {
				// TODO: check offset and clamp count
				return str_portion(_str + offset, count);
			}
		};

		template <class T>
		struct typeinfo {
			static const char * a() NOEXCEPT {
				str_portion part(__FUNCSIG__);
				return part.subview(ctti::ctti_begin).data();
			}
		};

	}

	template<class T>
	NODISCARD CONSTEXPR inline cstr type_name() NOEXCEPT {
		typedef typename remove_reference<T>::type no_ref;
		return detail::typeinfo<no_ref>::a();
	}
}

CT_REGISTER_TYPENAME(int)
CT_REGISTER_TYPENAME(float)
