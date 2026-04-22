#pragma once
#include "HegemonicLogger.h"

namespace Hegemonic
{
    /**
     * INFO: Expects is responsible for holding the static calls to expects
     */
    class Expects
    {
    public:
        /**
         * INFO: expectEqual is responsible for checking if an expression is equal
         * 
         * @param bool aExpression - the expression that is to be checked
         * @param char* aFile - the file the expect comes from
         * @param i32 aLine - the line number in aFile the expect comes from
         */
        static bool expectEqual(bool aExpression, const char* aFile, i32 aLine);

        /**
         * INFO: expectNotEqual is responsible for checking if an expression is not equal
         * 
         * @param bool aExpression - the expression that is to be checked
         * @param char* aFile - the file the expect comes from
         * @param i32 aLine - the line number in aFile the expect comes from
         */
        static bool expectNotEqual(bool aExpression, const char* aFile, i32 aLine);

        /**
         * INFO: expectFloatApprox is responsible for checking if an expression is with some error to a value
         * 
         * @param float aExpected - the truth expectation
         * @param float aActual - the value to check
         * @param char* aFile - the file the expect comes from
         * @param i32 aLine - the line number in aFile the expect comes from
         */
        static bool expectFloatApprox(float aExpected, float aActual, const char* aFile, i32 aLine);

        /**
         * INFO: expectTrue is responsible for checking if an expression is true
         * 
         * @param bool aExpression - the expression that is to be checked
         * @param char* aFile - the file the expect comes from
         * @param i32 aLine - the line number in aFile the expect comes from
         */
        static bool expectTrue(bool aExpression, const char* aFile, i32 aLine);

        /**
         * INFO: expectTrue is responsible for checking if an expression is false
         * 
         * @param bool aExpression - the expression that is to be checked
         * @param char* aFile - the file the expect comes from
         * @param i32 aLine - the line number in aFile the expect comes from
         */
        static bool expectFalse(bool aExpression, const char* aFile, i32 aLine);
    };
}

#define EXPECTEQUAL(aExpected, aActual) (Hegemonic::Expects::Expects::expectEqual(aExpected==aActual, __FILE__, __LINE__));
#define EXPECTNOTEQUA(aExpected, aActual) (Hegemonic::Expects::Expects::expectNotEqual(aExpected==aActual, __FILE__, __LINE__));
#define EXPECTFLOATAPPROX(aExpected, aActual) (Hegemonic::Expects::Expects::expectFloatApprox(aExpected, aActual, __FILE__, __LINE__));
#define EXPECTTRUE(aActual)