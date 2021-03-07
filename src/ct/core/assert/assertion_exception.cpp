
#include <ct/core/assert/assertion_exception.hpp>
#include <ct/core/utils/helper_macros.hpp>

namespace ct {

	AssertionException::AssertionException(cstr file,
	                                       i32 line,
	                                       cstr function,
	                                       cstr expression,
	                                       cstr message) noexcept
	: Exception(message),
	  _file(file),
	  _line(line),
	  _function(function),
	  _expression(expression) {}

	AssertionException::AssertionException(const AssertionException & other) noexcept
	: Exception(other),
	  _file(other._file),
	  _line(other._line),
	  _function(other._function),
	  _expression(other._expression) {}

	AssertionException & AssertionException::operator=(AssertionException const & other) noexcept {
		_file = other._file;
		_line = other._line;
		_function = other._function;
		_expression = other._expression;
		detail::copy_exception_data(&other._data, &_data);
		return *this;
	}

	CT_FORCE_INLINE cstr AssertionException::file() const {
		return this->_file;
	}

	CT_FORCE_INLINE i32 AssertionException::line() const {
		return this->_line;
	}

	CT_FORCE_INLINE cstr AssertionException::function() const {
		return this->_function;
	}

	CT_FORCE_INLINE cstr AssertionException::expression() const {
		return this->_expression;
	}

} // namespace ct
