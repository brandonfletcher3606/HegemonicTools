#include "HegemonicExpects.h"

namespace Hegemonic
{
    bool Expects::expectEqual(bool aExpression, const char* aFile, i32 aLine)
    {
        if (!aExpression)
        {
            Hegemonic::logError("Expectation expectEqual Failed");
            Hegemonic::logError("\t", "File : ", aFile);
            Hegemonic::logError("\t", "Line : ", aLine);
        }
        return aExpression;
    }

    bool Expects::expectNotEqual(bool aExpression, const char* aFile, i32 aLine)
    {
        if (aExpression)
        {
            Hegemonic::logError("Expectation expectNotEqual Failed");
            Hegemonic::logError("\t", "File : ", aFile);
            Hegemonic::logError("\t", "Line : ", aLine);
        }
        return aExpression;
    }

    bool Expects::expectFloatApprox(float aExpected, float aActual, const char* aFile, i32 aLine)
    {
        if (fabs(aExpected - aActual) > 0.001f)
        {
            Hegemonic::logError("Expectation expectFloatApprox Failed");
            Hegemonic::logError("\t", "File : ", aFile);
            Hegemonic::logError("\t", "Line : ", aLine);
            return false;
        }
        return true;
    }

    bool Expects::expectTrue(bool aExpression, const char* aFile, i32 aLine)
    {
        if (!aExpression)
        {
            Hegemonic::logError("Expectation expectTrue Failed");
            Hegemonic::logError("\t", "File : ", aFile);
            Hegemonic::logError("\t", "Line : ", aLine);
        }
        return aExpression;
    }

    bool Expects::expectFalse(bool aExpression, const char* aFile, i32 aLine)
    {
        if (aExpression)
        {
            Hegemonic::logError("Expectation expectFalse Failed");
            Hegemonic::logError("\t", "File : ", aFile);
            Hegemonic::logError("\t", "Line : ", aLine);
        }
        return aExpression;
    }
}