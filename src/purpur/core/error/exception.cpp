
#include <purpur/core/error/exception.hpp>

namespace ppr {

	Exception::Exception(cstr message) noexcept
	: _message(message)
	{}

	Exception::Exception(const Exception &rhs) noexcept
	: _message(rhs._message)
	{}

	Exception::~Exception() noexcept {}

	cstr Exception::what() const noexcept {
		return this->_message ? this->_message : "Unknown exception";
	}

	Exception Exception::operator=(const Exception &rhs) noexcept {
		if (this == &rhs) {
            return *this;
        }

		return Exception(rhs);
	}

}
