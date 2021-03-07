
#include <ct/core/error/exception.hpp>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>




namespace ct {

	namespace detail {

		#ifdef __cplusplus
			template <typename T, u64 SizeOfArray>
			CONSTEXPR u64 countof(const T (&array)[SizeOfArray]) {
				return SizeOfArray;
			}
		#else
			#define countof(arr) (sizeof(arr) / sizeof(arr[0]))
		#endif

		void copy_exception_data(const exception_data * from, exception_data * to) {
			if (!from->what) {
				to->should_free = false;
				to->what = nullptr;
				return;
			}

			u64 length = strlen(from->what);
			if (length > 0) {
				length += 1;
				char * what;
				#if defined(_MSC_VER)
					what = (char *)malloc(sizeof(char)*length);
					// NOLINTNEXTLINE
				    strncpy_s(what, length, from->what, length);
				#else
					what = new char[length + 1u];
					strncpy(what, from->what, length);
					what[length] = '\0';
				#endif
				to->what = what;
				to->should_free = true;
			} else {
				to->should_free = false;
				to->what = nullptr;
			}
		}

		void destroy_exception_data(exception_data * data) {
			if (data->should_free) {
				free((void *)data->what);
				data->what = nullptr;
				data->should_free = false;
			}
		}
	}

	Exception::Exception(const char * const message) NOEXCEPT : _data() {
		detail::exception_data init = { message, true };
		detail::copy_exception_data(&init, &_data);
	}

	Exception::Exception(const Exception & other) NOEXCEPT : _data() {
		detail::copy_exception_data(&other._data, &_data);
	}

	Exception::~Exception() NOEXCEPT {
		detail::destroy_exception_data(&_data);
	}

	NODISCARD const char * Exception::what() const NOEXCEPT {
		return _data.should_free ? _data.what : "Unknown exception";
	}

	Exception Exception::operator=(const Exception & other) NOEXCEPT {
		if (this == &other) {
			return *this;
		}

		detail::destroy_exception_data(&_data);
		detail::copy_exception_data(&other._data, &_data);

		return *this;
	}

} // namespace ct
