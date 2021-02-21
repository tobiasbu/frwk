
#include <ct/core/assert/assertion_exception.hpp>
#include <ct/core/utils/helper_macros.hpp>

namespace ct {

	AssertionException::AssertionException(cstr file,
	                                       int32 line,
	                                       cstr function,
	                                       cstr expression,
	                                       cstr message) noexcept
	: Exception(message),
	  _file(file),
	  _line(line),
	  _function(function),
	  _expression(expression) {}

	AssertionException::AssertionException(const AssertionException & rhs) noexcept
	: Exception(rhs._message),
	  _file(rhs._file),
	  _line(rhs._line),
	  _function(rhs._function),
	  _expression(rhs._expression) {}

	AssertionException & AssertionException::operator=(AssertionException const & rhs) noexcept {
		_file = rhs._file;
		_line = rhs._line;
		_function = rhs._function;
		_expression = rhs._expression;
		_message = rhs._message;
		return *this;
	}

	CT_FORCE_INLINE cstr AssertionException::file() const {
		return this->_file;
	}

	CT_FORCE_INLINE int32 AssertionException::line() const {
		return this->_line;
	}

	CT_FORCE_INLINE cstr AssertionException::function() const {
		return this->_function;
	}

	CT_FORCE_INLINE cstr AssertionException::expression() const {
		return this->_expression;
	}

} // namespace ct
