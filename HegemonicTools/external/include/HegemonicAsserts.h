#pragma once

#include <intrin.h>
#include <string>

#include "HegemonicToolsDefines.h"

#define debugBreak() __debugbreak()

namespace Hegemonic
{
	/**
	 * INFO: reportFailur is responsible for logging the failure to the LogInterface and calling logFatal
	 * 
	 * @param char* aExpression - expression that is checked
	 * @param char* aMessage - message to be expressed
	 * @param char* aFile - the file the error comes from
	 * @param i32 aLine - the line aFile that causes the error
	 */
	void HEXPORT reportFailure(const char* aExpression, const char* aMessage, const char* aFile, i32 aLine);

	/**
	 * INFO: Asserts is responsible for holding the static calls to assert
	 */
	class HEXPORT Asserts
	{
	public:
		/**
		 * INFO: assert is responsible for checking an expression
		 * 
		 * @param bool aExpression - the expression to be checked
		 */
		static void assertion(bool aExpression);

		/**
		 * INFO: assert is responsible for checking an expression
		 * 
		 * @param bool aExpression - the expression to be checked
		 * @param char* aMessage - message to be expressed if there is a failure
		 */
		static void assertion(bool aExpression, const char* aMessage);

		/**
		 * INFO: assert is responsible for checking an expression
		 * 
		 * @param bool aExpression - the expression to be checked
		 * @param std::string aMessage - message to be expressed if there is a failure
		 */
		static void assertion(bool aExpression, std::string aMessage);

		/**
		 * INFO: assert is responsible for checking an expression
		 * 
		 * @param bool aExpression - the expression to be checked in boolean
		 * @param char* aExpressionString - the expression to be check in char* format
		 * @param std::string aMessage - message to be expressed if there is a failure
		 * @param char* aFileLocation - the file the possible error comes from
		 * @param i32 aLineNumber - the line number in aFileLocation the possible error comes from
		 */
		static void assertion(bool aExpression, const char* aExpressionString, const char* aMessage, const char* aFileLocation, i32 aLineNumber);
	};
}

#ifdef NDEBUG
	#define HASSERT(aExpression)  ((void)0)
	#define HASSERT_MSG(aExpression, aMessage)  ((void)0)
#else
	#define HASSERT(aExpression) (Hegemonic::Asserts::assertion(aExpression, #aExpression, "NONE", __FILE__, __LINE__))
	#define HASSERT_MSG(aExpression, aMessage) (Hegemonic::Asserts::assertion(aExpression, #aExpression, aMessage, __FILE__, __LINE__))
#endif






