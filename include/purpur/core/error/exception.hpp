
#ifndef _PURPURINA_EXCEPTION_HPP_
#define _PURPURINA_EXCEPTION_HPP_

#include <purpur/core/config.hpp>
#include <purpur/core/export.hpp>


namespace ppr {

	////////////////////////////////////////////////////////////
	/// \class Exception
	/// \brief Represents an Purpurina exception.
	///
	////////////////////////////////////////////////////////////
	class PURPURINA_CORE_API Exception {

		public:

			///
			/// \brief Default Constructor
			/// \param message Description of this message
			///
			explicit Exception(cstr message = "unknown") noexcept;

			///
			/// \brief Copy constructor
			///
			Exception(const Exception &rhs) noexcept;

			///
			/// \brief Destructor
			///
			virtual ~Exception() noexcept;

			///
			/// \brief Get string identifying this exception
			///
			/// \return A pointer to c-string with description related to this exception.
			///
			virtual cstr what() const noexcept;

			///
			/// \brief Copy exception
			///
			Exception operator=(const Exception& rhs) noexcept;

		protected:

			cstr _message;

	};

}

#endif
