////////////////////////////////////////////////////////////
// Chronotrix Framework
//
// \todo Copyright notice
//
////////////////////////////////////////////////////////////

#ifndef _CHRONOTRIX_FRWK_DEBUG_ASSERTION_EXCEPTION_HPP_
#define _CHRONOTRIX_FRWK_DEBUG_ASSERTION_EXCEPTION_HPP_

#include <ct/core/error/exception.hpp>
#include <ct/core/export.hpp>
#include <ct/config/types.hpp>

namespace ct {

	////////////////////////////////////////////////////////////
	/// \class AssertionException
	/// \brief Represents an assert exception.
	///
	/// This exception is generally throw in assertions using `CT_ASSERT`
	///
	////////////////////////////////////////////////////////////
	class CT_CORE_API AssertionException : Exception {
	private:
		cstr _file;
		i32 _line;
		cstr _function;
		cstr _expression;

	public:
		///
		/// \brief Constructor
		///
		/// \param file File path
		/// \param line Line number
		/// \param function Function signature
		/// \param expression Assert expression
		/// \param message Optional message
		///
		explicit AssertionException(cstr file,
		                            i32 line,
		                            cstr function,
		                            cstr expression,
		                            cstr message = "unknown") noexcept;

		///
		/// \brief Copy constructor
		///
		/// \param rhs AssertionException to copy
		///
		AssertionException(const AssertionException & rhs) noexcept;

		///
		/// \brief Copy exception
		///
		AssertionException & operator=(AssertionException const & rhs) noexcept;

		///
		/// \brief Get file path which has generated this exception
		///
		/// \return A pointer to c-string representing the file path.
		///
		cstr file() const;

		///
		/// \brief Get line number where was generated this exception
		///
		/// \return Line number
		///
		i32 line() const;

		///
		/// \brief Get function signature
		///
		/// \return A pointer to c-string representing the function signature
		///
		cstr function() const;

		///
		/// \brief Get assert expression
		///
		/// \return A pointer to c-string representing the expression
		///
		cstr expression() const;
	};

} // namespace ct

#endif

////////////////////////////////////////////////////////////
/// @file AssertionException.hpp
/// @ingroup debug
/// @author Tobias Ulrich <flamenco.bluegrass@gmail.com>
/// @date September 25, 2020
///
////////////////////////////////////////////////////////////
