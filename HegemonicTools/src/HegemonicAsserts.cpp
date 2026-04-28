#include "HegemonicAsserts.h"
#include "HegemonicLogger.h"

namespace Hegemonic
{
	void reportFailure(const char* aExpression, const char* aMessage, const char* aFile, i32 aLine)
	{
		Hegemonic::LogInterface::getInstance().logFatal("Assertion Failure: ", aExpression, 
											"\n           Message: ", aMessage, 
											"\n           File: ", aFile, 
											"\n           Line: ", aLine);
		debugBreak();
	}

	void Asserts::assertion(bool aExpression)
	{
		const char* expression = aExpression ? "True" : "False";
		reportFailure(expression, "", __FILE__, __LINE__);
	}

	void Asserts::assertion(bool aExpression, const char* aMessage)
	{
		const char* expression = aExpression ? "True" : "False";
		reportFailure(expression, aMessage, __FILE__, __LINE__);
	}

	void Asserts::assertion(bool aExpression, std::string aMessage)
	{
		const char* expression = aExpression ? "True" : "False";
		reportFailure(expression, aMessage.c_str(), __FILE__, __LINE__);
	}

	void Asserts::assertion(bool aExpression, const char* aExpressionString, const char* aMessage, const char* aFileLocation, i32 aLineNumber)
	{
		if (!aExpression)
		{
			reportFailure(aExpressionString, aMessage, aFileLocation, aLineNumber);
		}
	}
}