
#ifndef _CHRONOTRIX_FRWK_EXCEPTION_HPP_
#define _CHRONOTRIX_FRWK_EXCEPTION_HPP_

#include <ct/core/config.hpp>
#include <ct/core/export.hpp>
#include <ct/core/types.hpp>

namespace ct {

	////////////////////////////////////////////////////////////
	/// \class Exception
	/// \brief Represents an Chronotrix exception.
	///
	////////////////////////////////////////////////////////////
	class CT_CORE_API Exception {
	protected:
		cstr _message;

	public:
		////////////////////////////////////////////////////////////
		/// \brief Default Constructor
		/// \param message Description of this message
		///
		////////////////////////////////////////////////////////////
		explicit Exception(cstr message = "unknown") NOEXCEPT;

		////////////////////////////////////////////////////////////
		/// \brief Copy constructor
		///
		////////////////////////////////////////////////////////////
		Exception(const Exception & rhs) NOEXCEPT;

		////////////////////////////////////////////////////////////
		/// \brief Destructor
		///
		////////////////////////////////////////////////////////////
		virtual ~Exception() NOEXCEPT;

		///
		/// \brief Get string identifying this exception
		///
		/// \return A pointer to c-string with description related to this exception.
		///
		virtual const char * what() const NOEXCEPT;

		///
		/// \brief Copy exception
		///
		Exception operator=(const Exception & rhs) NOEXCEPT;
	};

} // namespace ct

#endif
