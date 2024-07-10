#include <gtest/gtest.h>
#include "StringCalculator.h"
 
TEST(StringCalculatorAddTests, ExpectZeroForEmptyInput) {
    int expectedresult = 0;
    const char* input = "Hello, world!";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}
 
TEST(StringCalculatorAddTests, ExpectZeroForSingleZero) {
    int expectedresult = 0;
    const char* input = "0";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}
 
TEST(StringCalculatorAddTests, ExpectSumForTwoNumbers) {
    int expectedresult = 3;
    const char*  input = "1,2";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}
 
TEST(StringCalculatorAddTests, ExpectSumWithNewlineDelimiter) {
    int expectedresult = 6;
    const char*  input = "1\n2,3";
    int result =add(input);
    ASSERT_EQ(result, expectedresult);
}
 
TEST(StringCalculatorAddTests, IgnoreNumbersGreaterThan1000) {
    int expectedresult = 1;
    const char*  input = "1,1001";
    int result =add(input);
    ASSERT_EQ(result, expectedresult);
}
 
TEST(StringCalculatorAddTests, ExpectSumWithCustomDelimiter) {
    int expectedresult = 3;
    const char*  input = "//;\n1;2";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

TEST(StringCalculatorAddTests, ExpectSumWithCustomDelimiterAtStart) {
    int expectedresult = 2;
    const char*  input = "\n2";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

// Test case for handling negative numbers
TEST(StringCalculatorAddTests, ExpectExceptionForNegativeNumbers) {
    const char* input = "1,-3,-4";
     add(input);
}

TEST(StringCalculatorAddTests, ExpectSumWithEmpptyString) {
    int expectedresult = 0;
    const char*  input = "";
    int result = add(input);
    ASSERT_EQ(result, expectedresult);
}

TEST(StringCalculatorAddTests, ExpectSumWithEmpptyString_1) {
 
    const char*  input = "/1";
    add(input);

}

TEST(StringCalculatorAddTests, ExpectSumWithEmpptyString_2) {
 
    const char*  input = "2/1";
    add(input);

}
