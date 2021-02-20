
#include <ct/core/error/exception.hpp>

namespace ct {

	Exception::Exception(cstr message) NOEXCEPT : _message(message) {}

	Exception::Exception(const Exception & rhs) NOEXCEPT : _message(rhs._message) {}

	Exception::~Exception() NOEXCEPT {}

	cstr Exception::what() const NOEXCEPT {
		return this->_message ? this->_message : "Unknown exception";
	}

	Exception Exception::operator=(const Exception & rhs) NOEXCEPT {
		if (this == &rhs) {
			return *this;
		}

		return Exception(rhs);
	}

} // namespace ct
