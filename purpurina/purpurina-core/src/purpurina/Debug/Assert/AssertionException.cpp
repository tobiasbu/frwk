
#include <purpurina/Debug/Assert/AssertionException.hpp>
#include <purpurina/Macros/HelperMacros.hpp>

namespace ppr {

	AssertionException::AssertionException(
	cstr file,
	int32 line,
	cstr function,
	cstr expression,
	cstr message) noexcept
	:
	_file(file),
	_line(line),
	_function(function),
	_expression(expression),
	Exception(message)
	{}

	AssertionException::AssertionException(const AssertionException& rhs) noexcept
	:
	_file(rhs._file),
	_line(rhs._line),
	_function(rhs._function),
	_expression(rhs._expression),
	Exception(rhs._message)
	{}

	AssertionException& AssertionException::operator=(AssertionException const& rhs) noexcept {
		_file = rhs._file;
		_line = rhs._line;
		_function = rhs._function;
		_expression = rhs._expression;
		_message = rhs._message;
		return *this;
	}

	PPR_ASSERT_ALWAYS_INLINE cstr AssertionException::file() const {
		return this->_file;
	}

	PPR_ASSERT_ALWAYS_INLINE int32 AssertionException::line() const {
		return this->_line;
	}

	PPR_ASSERT_ALWAYS_INLINE cstr AssertionException::function() const {
		return this->_function;
	}

	PPR_ASSERT_ALWAYS_INLINE cstr AssertionException::expression() const {
		return this->_expression;
	}

}
