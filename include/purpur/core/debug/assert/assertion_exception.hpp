////////////////////////////////////////////////////////////
// Purpurina Engine
//
// \todo Copyright notice
//
////////////////////////////////////////////////////////////
///
/// \ingroup purpurina-core
/// \file AssertionException.hpp
/// \author Tobias Ulrich <flamenco.bluegrass@gmail.com>
/// \date September 25, 2020
///
////////////////////////////////////////////////////////////

#ifndef _PURPURINA_FRWK_ASSERTION_EXCEPTION_HPP_
#define _PURPURINA_FRWK_ASSERTION_EXCEPTION_HPP_

#include <purpur/core/error/exception.hpp>
#include <purpur/core/export.hpp>
#include <purpur/core/types.hpp>

namespace ppr {

	////////////////////////////////////////////////////////////
	/// \class AssertionException
	/// \brief Represents an assert exception.
	///
	/// This exception is generally throw in assertions using `PPR_ASSERT`
	///
	////////////////////////////////////////////////////////////
	class PURPURINA_CORE_API AssertionException : Exception {
	private:
		cstr _file;
		int32 _line;
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
		                            int32 line,
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
		int32 line() const;

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

} // namespace ppr

#endif
